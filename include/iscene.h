#pragma once
#include "universe.h"

namespace GLIZ
{
  class IScene
  {
  public:
    virtual void SetLocation(int left, int bottom, int width, int height) = 0;
    virtual void SetUniverse(IUniverse* universe) = 0;
    virtual void SetProjection() = 0;
    virtual void Draw() = 0;
    virtual void Animate() = 0;
    virtual void OnSetViewport(int viewportW, int viewportH) = 0;
    virtual void OnMouseMove(int X, int Y) = 0;
    virtual void OnMouse(int button, int state, int X, int Y) = 0;
    virtual void OnKeyboard(unsigned char key, int x, int y) = 0;
  };
} // GLIZ
