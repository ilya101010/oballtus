#pragma once
#include "libs.h"
#include "dot.h"

namespace GLIZ
{
    class IElement
    {
    public:
        virtual void DrawGL()=0;
        virtual void GMove(Vec v)=0; // geometric move
        bool drawable = true;
    };

    inline ostream& operator<<(ostream& os, const IElement& d)
    {
        os << "ielement {}";
        return os;
    }
} // GLIZ
