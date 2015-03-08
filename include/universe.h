#pragma once
#include "libs.h"
#include "dot.h"
#include "object.h"
#include "collision.h"
#include "ball.h"
#include "borders.h"
#include "timeline.h"
#include "text.h"

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
                if(objects[i]) objects[i]->element->DrawGL();
            }
        }

        virtual void MoveObjects()=0;
        virtual void OnClick(double x, double y)=0;
    };

    class MyUniverse : public IUniverse, public CollisionManager
    {
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
            Object *obj = new Ball(); Add(obj);
            Borders *bor = new Borders(); ifstream f("test");

            bor->Read(f);
            Add(bor);
            ball().sphere().r=borders().BallR();
            //Object *a = new Object(); a->element=q;
            //Add(a);
        }
        ~MyUniverse() {}

        void OnClick(double x, double y)
        {
            Dot c = ball().sphere().c;
            Vec vv = (Vec(x,y)-c);
            Vec v = vv.normalize(0.02);
            ball().v=v;
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

    class EditUniverse : public IUniverse
    {
    public:
        EditUniverse()
        {
            Object *bg = new Object();
                Quad *q = new Quad();
                q->a=q->a*4; q->b=q->b*4; q->c=q->c*4; q->d=q->d*4;
                q->bl=1; q->r=rand(); q->g=0.5;
                bg->element=q;
            Add(bg);
            Object *tt = new Object();
                TextEl *t = new TextEl("EditScene"); tt->element=t;
            Add(tt);
        }
        ~EditUniverse() {}

        void OnClick(double x, double y)
        {
        }

        void MoveObjects()
        {

        }
    };
}
