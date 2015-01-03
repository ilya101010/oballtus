#pragma once
#include "sphere.h"
#include "object.h"
#include "libs.h"

namespace GLIZ
{
    class Ball: public Object
    {
    public:
        Ball()
        {
            //f.push_back(Force(0.5,0.25,0));
            v = Vec(0,0);
            element=new Sphere();
            //m = 10;
        }
        inline Sphere& sphere()
        {
            return *(static_cast<Sphere*>(element));
        }
        void React()
        {
            //cout << Reflect(v,{Dot(s.r-1,s.r-1),Dot(s.r-1,1-s.r)}) << ";" << Reflect(v,{Dot(1-s.r,s.r-1),Dot(s.r-1,s.r-1)}) << endl;
            if(sphere().c.x >= 1-sphere().r || sphere().c.x <= sphere().r-1)
                v=Reflect(v,{Dot(sphere().r-1,sphere().r-1),Dot(sphere().r-1,1-sphere().r)});
            if(sphere().c.y >= 1-sphere().r || sphere().c.y <= sphere().r-1)
                v=Reflect(v,{Dot(1-sphere().r,sphere().r-1),Dot(sphere().r-1,sphere().r-1)});
        }
    };
}

