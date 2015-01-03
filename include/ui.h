#pragma once
#include "libs.h"
#include "iscene.h"
#include "scene.h"

namespace GLIZ
{
    class UI
    {
        vector<IScene*> _scenes;
    public:
        UI()
        {
            IScene* scene; scene = new Scene2d();
            _scenes.push_back(scene);
        }

        ~UI()
        {
            for(int i = 0; i<_scenes.size(); i++)
            {
                if(_scenes[i]) delete _scenes[i];
            }
        }

        void SetViewport(int Width, int Height)
        {
            glViewport(0, 0, Width, Height);
            glMatrixMode(GL_PROJECTION);
            for(int i = 0; i<_scenes.size(); i++)
            {
                IScene* scene = _scenes[i];
                if(scene) scene->OnSetViewport(Width, Height);
            }
        }

    public:
        inline static UI& Get()
        {
            static UI globalUI;
            return globalUI;
        }

        void AttachUniverse(int scene_i, IUniverse* universe)
        {
            IScene *scene = _scenes[scene_i];
            scene->SetUniverse(universe);
        }

        void Draw()
        {
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            for(int i = 0; i<_scenes.size(); i++)
            {
                IScene* scene = _scenes[i];
                if(scene) scene->Draw();
            }
            glutSwapBuffers();
        }

        void Idle()
        {
            for(int i = 0; i<_scenes.size(); i++)
            {
                IScene* scene = _scenes[i];
                if(scene) scene->Animate();
            }
            glutPostRedisplay();
            glutSwapBuffers();
            glutTimerFunc(C_TMS,&UI::Glut_Timer,0);
        }

        void Mouse(int button, int state, int x, int y)
        {
            for(int i = 0; i<_scenes.size(); i++)
            {
                IScene* scene = _scenes[i];
                if(scene) scene->OnMouse(button,state,x,y);
            }
        }

        static void Glut_Draw()
        {
          Get().Draw();
        }

        static void Glut_Idle()
        {
            Get().Idle();
        }

        static void Glut_Mouse(int button, int state, int x, int y)
        {
            return Get().Mouse(button,state,x,y);
        }

        static void Glut_Timer(int)
        {
            Get().Idle();
        }
    };
} // GLIZ
