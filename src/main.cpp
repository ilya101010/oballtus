#include <iostream>
#include "libs.h"
#include "dot.h"
#include "universe.h"
#include "sphere.h"
#include "ui.h"
#include "ball.h"
#include "borders.h"
using namespace GLIZ;

int window;

MyUniverse universe;

void ResizeUI(int W, int H)
{
    if(H==0) H=1;
    UI& ui = UI::Get();
    ui.SetViewport(W,H);
}

void InitGL(int W, int H)
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    ResizeUI(W, H);
}

int main(int argc, char **argv)
{
    UI::Get().AttachUniverse(0,&universe);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Oballtus by ilya101010");
    glutDisplayFunc(&UI::Glut_Draw);
    glutTimerFunc(C_TMS,&UI::Glut_Timer,0);
    glutMouseFunc(&UI::Glut_Mouse);
    glutKeyboardFunc(&UI::Glut_Keyboard);
    glutReshapeFunc(&ResizeUI);
    InitGL(640, 480);
    glutMainLoop();
    return 1;
}