#pragma once
#include "libs.h"
#include "ielement.h"
#include "timeline.h"
#include "dot.h"

namespace GLIZ
{
    class Object
    {
    public:
        IElement *element; // graphical element
        vector<Force> f; // force
        Vec v = Dot(0,0,0); // velocity
        Vec a = Dot(0,0,0); // accelaration
        bool Movable;
        double m;
        Object() : m(1) {Movable = true;}
        ~Object() {}

        void Move(int dt) // milliseconds
        {
            if(!Movable) return;
            element->GMove(v*0.02*dt);
        }
        virtual void React() {}
        /*
        virtual void React()
        {
            if (collisionMarked)
            {
                v = Reflect(v,collisionPlane)
            }
            collisionMark = false;
        }

        void MarkCollision(Vec collisionPlane)
        {
            collisionMark = true;
            this->collisionPlane = collisionPlane;
        }
        */
    };
}
