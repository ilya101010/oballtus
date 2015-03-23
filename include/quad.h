#pragma once
#include "ielement.h"
#include "dot.h"
#include "libs.h"

namespace GLIZ
{
    class Quad: public IElement
    {
    public:
        Dot a, b, c, d;
        GLfloat r,g,bl,al;
        Quad()
        {r=1;g=0.25;bl=0.25; al=0.5; a = Dot(-0.25,0.25);b=Dot(0.25,0.25);c=Dot(0.25,-0.25);d=Dot(-0.25,-0.25);}
        Quad(Dot a, Dot b, Dot c, Dot d) { r=1;g=0.25;bl=0.25; al=1; this->a=a, this->b=b, this->c=c, this->d=d; }
        void DrawGL()
        {
            glBegin(GL_QUADS);
                glColor4f(r,g,bl,al);
                glVertex3d(a.x,a.y,a.z);
                glVertex3d(b.x,b.y,b.z);
                glVertex3d(c.x,c.y,c.z);
                glVertex3d(d.x,d.y,d.z);
            glEnd();
        }
        void GMove(Vec v)
        {
            a=a+v,b=b+v,c=c+v,d=d+v;
        }
    };
    inline ostream& operator<<(ostream& os, const Quad& d)
    {
        os << "quad { a="<< d.a << "; b=" << d.b << "; c=" << d.c << "; d=" << d.d << "}";
        return os;
    }
    class Rectangle: public Quad
    {
    public:
        Rectangle(Dot a, Dot b) : Quad(a,Dot(b.x,a.y),b,Dot(a.x,b.y)) {}
    };
}
