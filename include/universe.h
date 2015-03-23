#pragma once
#include "libs.h"
#include "dot.h"
#include "object.h"
#include "collision.h"
#include "ball.h"
#include "borders.h"
#include "timeline.h"
#include "text.h"
#include "line.h"

namespace GLIZ
{
    class IUniverse
    {
    public:
        vector<Object*> objects;
        void Add(Object* obj)
        {
            objects.push_back(obj);
        }

        void Draw()
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            for(int i = 0; i<objects.size(); i++)
            {
                glColor4f(1,1,1,1);
                if(objects[i] && objects[i]->element->drawable) objects[i]->element->DrawGL();
            }
        }

        virtual void MoveObjects()=0;
        virtual void OnClick(double x, double y)=0;
        virtual void OnKeyboard(unsigned char key, int x, int y)=0;
        //virtual void OnKeyboard(double )
    };

    class MyUniverse : public IUniverse, public CollisionManager
    {
        bool editmode;
        bool dotmode;
    public:
        inline Borders& borders()
        {
            return *(static_cast<Borders*>(objects[1]));
        }
        inline Ball& ball()
        {
            return *(static_cast<Ball*>(objects[0]));
        }

        MyUniverse()
        {
            editmode = dotmode =false;

            Object *obj = new Ball(); Add(obj);
            Borders *bor = new Borders(); ifstream f("test");
            bor->Read(f);
            Add(bor); // 1
            ball().sphere().r=borders().BallR(); ball().sphere().c.z=0;
            // edit mode
            Object *bg = new Object();
                Quad *q = new Quad(); q->drawable=false;
                q->a = Dot(-1,1,-1);q->b=Dot(1,1,-1);q->c=Dot(1,-1,-1);q->d=Dot(-1,-1,-1);
                q->bl=1; q->r=0.75; q->g=0.5; q->al=0.5;
                bg->element=q;
            Add(bg); // 2
            Object *tt = new Object();
                TextEl *t = new TextEl("Editing mode"); tt->element=t; tt->element->drawable=false;
            Object *tt1 = new Object();
                TextEl *t1 = new TextEl("Place dots by clicking"); tt1->element=t1; tt1->element->drawable=false;
            Add(tt); // 3
            Add(tt1); // 4
        }
        ~MyUniverse() {}

        void OnClick(double x, double y)
        {
            if(dotmode)
            {
                return;
            }
            Dot c = ball().sphere().c;
            Vec vv = (Vec(x,y)-c);
            Vec v = vv.normalize(0.02);
            ball().v=v;
        }

        void OnKeyboard(unsigned char key, int x, int y)
        {
            if(key == 'e' || key == 'E')
            {
                objects[2]->element->drawable=!objects[2]->element->drawable;
                objects[3]->element->drawable=!objects[3]->element->drawable;
                editmode = !editmode;
            }
            if(editmode && (key == 'd' || key == 'D'))
            {
                objects[3]->element->drawable=!objects[3]->element->drawable;
                objects[4]->element->drawable=!objects[4]->element->drawable;
                ball().Movable = !ball().Movable;
                dotmode = !dotmode;
            }
        }

        void MoveObjects()
        {
            int dt = C_TMS;
            // moving things
            for(int i=0; i<objects.size(); i++)
                objects[i]->Move(dt);
            // colliding things
            bool fCollision = false;
            for(int i = 0; i<borders().model().elements.size(); i++)
            {
                Quad q = borders().quad(i);
                Line* rl = ReflectLine(&ball().sphere(),&q, true); // only edges!
                if(rl != NULL)
                    if (normal(*rl)*ball().v < 0)
                    { ball().v = Reflect(ball().v,{rl->first,rl->second}), cout << "yeah"; fCollision = true; break; }
            }
            if (!fCollision)
                for(int i = 0; i<borders().model().elements.size(); i++)
                {
                    Quad q = borders().quad(i);
                    Line* rl = ReflectLine(&ball().sphere(),&q); // only edges!
                    if(rl != NULL)
                        if (normal(*rl)*ball().v < 0)
                        {
                            ball().v = Reflect(ball().v,{rl->first,rl->second});
                            cout << "yeah"; break;
                        }
                }
            // reacting things (just do nothing!)
            for(int i = 0; i<objects.size(); i++)
                objects[i]->React();
        }
    };
}
