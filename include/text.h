#pragma once
#include "libs.h"
#include "object.h"

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
            c = Dot(-0.9,0.9);
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
    /*
    class Font
    {
    public:
        FTFont* font;
        Font(string ttf, int size)
        {
            font = new FTGLBitmapFont(ttf.c_str());
            if(!font->FaceSize(size))
            {
                cout << "ERROR: Text->FaceSize" << endl;
                exit(1);
            }
            font->Depth(1.0);
            font->CharMap(ft_encoding_unicode);
        }
        void Render(Dot c, string text)
        {
            glPushMatrix();
                glTranslatef(c.x,c.y,-1);
                font->Render(text.c_str());
            glPopMatrix();
        }
        void GMove() {}
    };*/
}
