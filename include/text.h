#pragma once
#include "libs.h"

namespace GLIZ
{
    class TextEl: public IElement
    {
    public:
        string text;
        void *font;
        Dot c;
        TextEl()
        {
            font = GLUT_BITMAP_HELVETICA_18;
            text = "Hello World";
            c = Dot(0,0);
        }
        TextEl(string value): text(value)
        {
            font = GLUT_BITMAP_HELVETICA_18;
            c = Dot(0,0);
        }
        void DrawGL()
        {
            glRasterPos2f(c.x,c.y);
            for(int i = 0; i<text.length(); i++)
                glutBitmapCharacter(font,text[i]);
        }
        void GMove(Vec v)
        {
            c=c+v;
        }
    };
}
