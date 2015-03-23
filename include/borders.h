#pragma once
#include "libs.h"
#include "dot.h"
#include "object.h"
#include "model.h"
#include "quad.h"
#include "line.h"

namespace GLIZ
{
    class Borders : public Object
    {
    public:
        inline Model& model()
        {
            return *(static_cast<Model*>(element));
        }
        Borders() {Movable = false; element=new Model(); br=-1;}
        int w, h;
        double br;
        Dot s; Dot l;
        vector<vector<bool> > walls;
        void ToModel()
        {
            for(int y=0; y<h; y++)
                for(int x=0; x<w; x++)
                {
                    if(walls[y][x])
                    {
                        IElement* a = new Rectangle(Dot(-1+2.0*x/w,-1+2.0*y/h,0),Dot(-1+2.0*(x+1)/w,-1+2.0*(y+1)/h,0));
                        model().elements.push_back(a);
                    }
                }
            return;
        }
        void Read(istream& in) // TODO: # - walls; X - ball; O - loose
        {
            if(!in)
            {
                w=h=0;
                br=0.02;
                return;
            }
            in>>w>>h;
            in>>br;
            walls.resize(h); for(int i = 0; i<h; i++) walls[i].resize(w, false);
            for(int y=0; y<h; y++)
                for(int x=0; x<w; x++)
                {
                    char t; in>>skipws>>t;
                    if(t == 'X') s=Dot(x,y);
                    else if(t == 'O') l=Dot(x,y);
                    else if (t=='#') walls[y][x]=true;
                }
            ToModel();
        }
        inline Quad& quad(int i)
        {
            return *(static_cast<Quad*>(model().elements[i]));
        }

        double BallR()
        {
            return br;
        }

    };

    class PolyChain: public Object
    {
        vector<Line> lines;
        inline Model& model()
        {
            return *(static_cast<Model*>(element));
        }
        void AddLine(Line a)
        {
            LineEl *t = new LineEl(a);
            model().elements.push_back(t);
        }
        inline void AddDot(Dot a)
        {
            AddLine(Line(lines.back().second, a));
        }
        PolyChain(vector<Line> lines)
        {
            element = new Model();
            for(vector<Line>::iterator i = lines.begin(); i != lines.end(); i++)
                AddLine(*i);
        }
        PolyChain(vector<Dot> dots)
        {
            AddLine(Line(dots[0],dots[1]));
            for (int i = 2; i<dots.size(); i++)
                AddDot(dots[i]);
        }
    };
}
