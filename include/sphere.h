#pragma once
#include "libs.h"
#include "ielement.h"
#include "dot.h"

namespace GLIZ
{
    class Sphere: public IElement
    {
        GLUquadric* _q;
        inline void Clear() {_q = NULL;}
        inline bool _Inited() {return _q;}
        inline void Init()
        {
            if (_Inited()) return;
                _q = gluNewQuadric();
        }
    public:
        Dot c; // center
        double r; // radius
        int slices, stacks;
        Sphere()
        {
            r=0.125, c.x=c.y=c.z=0;
            slices=stacks=20;
            Clear();
        }
        Sphere(double x, double y, double z, double r) {c.x=x, c.y=y, c.z=z; slices=stacks=20; this->r=r; Clear();}
        ~Sphere() {if(_q) gluDeleteQuadric(_q);}
        void DrawGL()
        {
            Init();
            glColor3f(1,1,1);
            glPushMatrix();
            {
                glTranslated(c.x,c.y,c.z);
                gluSphere(_q,r,slices,stacks);
            }
            glPopMatrix();
        }
        void GMove(Vec v)
        {
            c=c+v;
        }
    };

    inline ostream& operator<<(ostream& os, const Sphere& m)
    {
        os << "sphere {center {"<< m.c <<"}; radius="<<m.r<<"}";
        return os;
    }
}
