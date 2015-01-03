#pragma once
#include "libs.h"
#include "dot.h"
#include "object.h"
#include "model.h"
#include "quad.h"

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
                        IElement* a = new Rectangle(Dot(-1+2.0*x/w,-1+2.0*y/h),Dot(-1+2.0*(x+1)/w,-1+2.0*(y+1)/h));
                        model().elements.push_back(a);
                    }
                }
            return;
        }
        void Read(istream& in) // TODO: # - walls; X - ball; O - loose
        {
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

    /*
    class CollisionManager()
    {
        void SearchCollisions(vector<Object>& objects)
        {
            vector<Object>::size_type n = objects.size();
            //
            for (int i = 0; i < n; i++)
            {
                object& A = objects[i];
                if (!A.Static)
                    for (int j = 0; j < n; j++)
                        if (i != j)
                        {
                            object& B = objects[j];
                            //
                            // testing collision...
                            //
                            A.MarkCollision();
                        }
            }
        }
    }
    */
}
