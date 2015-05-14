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

int main(int argc, char **argv)
{
    UI::Get().AttachUniverse(0,&universe);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Oballtus by ilya101010");
    //glewInit();
    glutDisplayFunc(&UI::Glut_Draw);
    glutTimerFunc(C_TMS,&UI::Glut_Timer,0);
    glutMouseFunc(&UI::Glut_Mouse);
    glutKeyboardFunc(&UI::Glut_Keyboard);
    glutReshapeFunc(&UI::ResizeUI);
    UI::Get().InitGL(640, 480);
    glutMainLoop();
    return 1;
}