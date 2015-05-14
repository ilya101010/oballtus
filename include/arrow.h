#pragma once

#include "ielement.h"

namespace GLIZ
{
    class Arrow: public IElement
    {
    public:
        Dot a, b;
        GLfloat width;
        float aw, ah;
        Arrow(Dot a, Dot b)
        {
            this->a=a; this->b=b;
            width=1;
        }

        Arrow(Dot a, Dot b, GLfloat width)
        {
            this->a=a; this->b=b;
            this->width=width;
        }

        void DrawGL()
        {
            glLineWidth(width);
            glColor3f(0.25,0.42,1.0);
            glBegin(GL_LINES);
                glVertex2f(a.x,a.y);
                glVertex2f(b.x,b.y);
            glEnd();
        }

        void GMove(Vec v)
        {
            a = a+v; b = b+v;
        }
    };
}