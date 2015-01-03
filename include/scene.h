#pragma once
#include "libs.h"
#include "universe.h"
#include "iscene.h"

namespace GLIZ
{
    class BaseScene: public IScene
    {
    protected:
        int X0, Y0;
        int W, H;
        IUniverse* universe;
    public:
        BaseScene() {}
        void SetLocation(int left, int bottom, int width, int height)
        {
            X0=left, Y0=bottom, W=width, H=height;
        }
        void SetUniverse(IUniverse* universe)
        {
            this->universe=universe;
        }
        void Draw()
        {
            if(universe) universe->Draw();
        }
    };

    class Scene2d: public BaseScene
    {
        double cX, cY; double M;
    public:
        Scene2d()
        {
            cX=cY=0;
            M=1;
        }
        Scene2d(double cX, double cY, double M): cX(this->cX),cY(this->cY),M(this->M)
        {
        }
        void SetProjection(){}
        void OnSetViewport(int viewportW, int viewportH)
        {
            W=viewportW; H=viewportH;
            double sY = M*H, sX = M*W;
            gluOrtho2D(-1/M,1/M,-1/M,1/M);
        }

        void Animate()
        {
            universe->MoveObjects();
        }
        void OnMouseMove(int X, int Y)
        {

        }

        void OnMouse(int button, int state, int X, int Y)
        {
            double x=(1.0*X)/W, y=(1.0*Y)/H;
            if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                universe->OnClick(-1+2*x,-1+2*(1-y));
        }
    };
}
