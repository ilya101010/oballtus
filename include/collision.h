#pragma once
#include "ielement.h"
#include "quad.h"
#include "sphere.h"

namespace GLIZ
{
    class CollisionManager
    {
    protected:
        CollisionManager() {} // cannot instantiate
    private: // only for me
    public: // for external usage
        bool commonSectionCircle(Line k, Sphere *s)
        {
            double x1=k.first.x, y1=k.first.y, x2=k.second.x, y2=k.second.y, xC = s->c.x, yC = s->c.y, R = s->r;
            x1 -= xC; y1 -= yC; x2 -= xC; y2 -= yC;
            double dx=x2-x1,dy=y2-y1;
            double a=dx*dx+dy*dy, b=2.*(x1*dx+y1*dy), c=x1*x1+y1*y1-R*R;
            if(-b<0) return (c<0);
            if(-b<(2.*a)) return ((4.*a*c - b*b) < 0);
            return (a+b+c<0);
        }
        static inline bool Intersection(Line k, Sphere *s)
        {
            double x1=k.first.x, y1=k.first.y, x2=k.second.x, y2=k.second.y, cx = s->c.x, cy = s->c.y, R = s->r;
            double f1 = (x2-x1)*(cx-x1)+(y2-y1)*(cy-y1);
            double f2 = (x1-x2)*(cx-x2)+(y1-y2)*(cy-y2);
            double f3 = (cx-x1)*(y2-y1)-(cy-y1)*(x2-x1); // == |грани| * длину вертикальной проекции
            double f4 = f3*f3/((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
            if (f1 > 0 && f2 > 0 // && f3 > 0
                    && f4 <= R*R)
                return true;
            return false;
        }


        inline static Line* ReflectLine(Sphere* s, Quad* q, bool onlyEdge = false) // return reflection line (new reference)
        {
            // data
            Dot a = q->a;
            Dot b = q->b;
            Dot c = q->c;
            Dot d = q->d;
            Dot SC = s->c;
            bool Fa = (s->c.DistTo(q->a) < s->r), Fb = (s->c.DistTo(q->b) < s->r), Fc = (s->c.DistTo(q->c) < s->r), Fd = (s->c.DistTo(q->d) < s->r);
            Dot av(0,0);
            if (Fa+Fb+Fc+Fd != 0) av = ((Fa ? a : Dot(0,0)) + (Fb ? b : Dot(0,0)) + (Fc ? c : Dot(0,0)) + (Fd ? d : Dot(0,0)))*(1.0/(Fa+Fb+Fc+Fd));
            bool FvertexColl = Fa || Fb || Fc || Fd;
            bool Fab = Intersection({q->a,q->b},s);
            bool Fbc = Intersection({q->b,q->c},s);
            bool Fcd = Intersection({q->c,q->d},s);
            bool Fda = Intersection({q->d,q->a},s);
            bool FedgeColl = Fab || Fbc || Fcd || Fda;
            // decisions
            // Eigen!
            if (FedgeColl)
            {
                if(Fab) {return new Line(a,b);}
                if(Fbc) {return new Line(b,c);}
                if(Fcd) {return new Line(c,d);}
                if(Fda) {return new Line(d,a);}
            }
            else if(FvertexColl && (!onlyEdge))
            {
                vector<Dot> k;
                if(Fa) k.push_back(q->a);
                if(Fb) k.push_back(q->b);
                if(Fc) k.push_back(q->c);
                if(Fd) k.push_back(q->d);
                if(k.size() >= 3)
                    return NULL;
                if (Fa+Fb+Fc+Fd!=1)
                {
                    int stop = 1;
                }

                return new Line(Dot(av.x+SC.y-av.y,av.y-SC.x+av.x),av);
            }
            return NULL;
        }
/*
        inline bool Collision(IElement* o1, IElement* o2)
        {
            string type1 = o1->GetType();
            string type2 = o2->GetType();
            if (type1 == "Borders" && type2 == "Sphere")
            {
                return Collision_Borders_Sphere(o1,o2);
            }
        }
*/


    public: // just a part of public zone of a parent component
    };

}
