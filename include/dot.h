#pragma once
#include "libs.h"

namespace GLIZ
{
    class Dot
    {
        //friend ostream& operator<<(ostream& os, const Dot& d);
    public:
        double x, y, z;
        Dot() : x(0), y(0), z(0) {}
        Dot(double x, double y){this->x=x, this->y=y, this->z=0;}
        Dot(double x, double y, double z) {this->x=x, this->y=y, this->z=z;}
        bool operator==(const Dot& b) const {return (x==b.x)&&(y==b.y)&&(z==b.z);}
        bool operator!=(const Dot& b) const {return !((x==b.x)&&(y==b.y)&&(z==b.z));}
        Dot operator+(const Dot& b) const {return Dot(x+b.x, y+b.y, z+b.z);}
        Dot operator*(double m) const {return Dot(x*m,y*m,z*m);}
        Dot operator-(const Dot& b) const {return Dot(this->x,this->y,this->z)+b*(-1);}
        double DistTo(Dot a) const {return sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y)+(a.z-z)*(a.z-z));}
        double operator*(const Dot&b) const {return x*b.x+y*b.y+z*b.z;} // only for Vec
        Dot normalize(const double k = 1) const { double m = k/DistTo(Dot(0,0)); return Dot(x,y,z)*m; } // only for Vec
    };
    typedef Dot Vec;
    typedef Dot Force;
    typedef pair<Dot, Dot> Line;
    
    inline Vec Reflect(const Vec& l, const Line& line)
    {
        const Dot& a = line.first;
        const Dot& b = line.second;
        Vec n = Vec(a.y-b.y,b.x-a.x);
        Vec r = l-(n*2)*((l*n)/(n*n));
        return r;
    }

    inline Vec normal(const Line& line)
    {
        const Dot& a = line.first;
        const Dot& b = line.second;
        return Vec(b.y-a.y, a.x-b.x);
    }

    inline ostream& operator<<(ostream& os, const Dot& d)
    {
        os << "dot { (" << d.x << ';' << d.y << ';' << d.z << ") }";
        return os;
    }

}



/*

  <(u1,v1), (u2,v2)> = u1*u2+v1*v2 = |u|*|v|*cos(b)

  length^2 = <(u1,v1),(u1,v1)> = u1^2+v1^2

  l-2n*(|l|*|n|*cos(b))/(|n|^2)=l-2*|l|*cos(b)*(n/|n|)

  x = a.x + (b.x-a.x) * t
  x = a.y + (b.y-a.y) * t
  
  (x-s.c.x)^2 + (y-s.c.y)^2 = r^2
  
  
  
  
  
  
  
  
 */
