#pragma once
#include "libs.h"
#include "ielement.h"
#include "dot.h"

namespace GLIZ
{
    class LineEl: public IElement
    {
    public:
        Dot a, b;
        GLfloat width;
        LineEl()
        {
            a = Dot(0,0); b = Dot(1,1);
            width = 1;
        }
        LineEl(Dot a, Dot b) : a(this->a), b(this->b)
        {
            width = 1;
        }
        LineEl(Dot a, Dot b, GLfloat width) : a(this->a), b(this->b), width(this->width) {}
        void DrawGL()
        {
            glLineWidth(width);
            glColor3f(1,1,1);
            glBegin(GL_LINES);
                glVertex3f(a.x,a.y,a.z);
                glVertex3f(b.x,b.y,b.z);
            glEnd();
        }
        LineEl(Line k)
        {
            a=k.first;
            a=k.second;
            width=1;
        }
        void GMove(Vec v)
        {
            a=a+v; b=b+v;
        }
        Line ToLine()
        {
            return Line(a,b);
        }
    };
} // GLIZ
