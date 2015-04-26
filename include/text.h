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
    // TODO: implement FreeType
    /*class TextEl2: public IElement
    {
        FT_Library ft;
    public:
        FT_Face face;
        TextEl2()
        {
            drawable=true;
            FT_Error e;
            e = FT_Init_FreeType(&ft); if(e) cout << "Error: init";
            e = FT_New_Face(ft, "/home/ilya101010/ClionProjects/oballtus/Terminus.ttf", 0, &face); if(e) cout << "Error: FT_NEW_FACE";
            e = FT_Set_Char_Size(face, 0, 16*64, 300, 300); if(e) cout << "Error: FT_Set_Char_Size";
            e = FT_Load_Glyph(face,FT_Get_Char_Index(face, 'A'),FT_LOAD_DEFAULT); if(e) cout << "Error: FT_Load_Glyph";
        }
        void DrawGL()
        {
            FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL);
        }
        void GMove(Vec v)
        {

        }
    };*/
}
