#pragma once
#include "libs.h"
#include "dot.h"
#include "object.h"
#include "collision.h"
#include "ball.h"
#include "borders.h"
#include "timeline.h"
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
            for(int i = 0; i<objects.size(); i++)
                if(objects[i]) objects[i]->element->DrawGL();
        }

        virtual void MoveObjects()=0;
        virtual void OnClick(double x, double y)=0;
    };
    /*
    class Universe :
    {
    public:
        vector<Object*> objects;
        Universe(){}
        ~Universe(){}

        void Add(Object* obj)
        {
            objects.push_back(obj);
        }

        void MoveObjects()
        {
            //TimeLine::Time
            int dt = C_TMS;
            if (!dt) return;

            // 1. Movements

            for(int i = 0; i<objects.size(); i++)
                objects[i]->Move(dt);

            // 2. Collisions

            

            // 3. Appear / Disappear

            // 4. React


            for(int i = 0; i<objects.size(); i++)
                objects[i]->React();
            //
            /*
            colisMgr.SearchCollisions(objects);
            for(int i = 0; i<objects.size(); i++)
                objects[i]->React();

        }
    };
    */

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
}
