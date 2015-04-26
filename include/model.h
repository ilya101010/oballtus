#pragma once
#include "ielement.h"
#include "libs.h"

namespace GLIZ
{
    class Model : public IElement
    {
    public:
        vector<IElement*> elements;
        Model() {}
        void DrawGL()
        {
            for(int i = 0; i<elements.size(); i++)
                elements[i]->DrawGL();
        }
        void GMove(Vec v)
        {
            for(int i = 0; i<elements.size(); i++)
                elements[i]->GMove(v);
        }
    };

    inline ostream& operator<<(ostream& os, const Model& m)
    {
        os << "model (" << m.elements.size() <<" elements) {" << endl;
        for(int i = 0; i<m.elements.size(); i++)
            os << *m.elements[i] << endl;
        os << "}";
    }
}
