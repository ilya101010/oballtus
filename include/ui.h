#pragma once
#include "libs.h"
#include "iscene.h"
#include "scene.h"
//#include "shader.h"

namespace GLIZ
{
    class UI
    {
        vector<IScene*> _scenes;
        //ShaderProgram* shaderProgram;
    public:
        UI()
        {
            IScene* scene2d; scene2d = new Scene2d();
            _scenes.push_back(scene2d);
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
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            //glUseProgram(shaderProgram->ID);

            for(int i = 0; i<_scenes.size(); i++)
            {
                IScene* scene = _scenes[i];
                if(scene) scene->Draw();
            }
            glutSwapBuffers();
        }

        inline static void ResizeUI(int W, int H)
        {
            if(H==0) H=1;
            UI::Get().SetViewport(W,H);
        }

        void InitGL(int W, int H)
        {
            glClearColor(0.0f,0.0f,0.0f,0.0f);
            glClearDepth(1.0); // def - 1.0
            glDepthFunc(GL_LESS); // def - GL_LESS
            glEnable(GL_DEPTH_TEST);
            glShadeModel(GL_SMOOTH);
            ResizeUI(W, H);
            // TODO: shaders
            /*
            cout << "InitGL: before shaders";
            shaderProgram = new ShaderProgram("shaders/in");
            shaderProgram->AddShader(GL_VERTEX_SHADER);
            shaderProgram->Create();
             */
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

        void Keyboard(unsigned char key, int x, int y)
        {
            for(int i = 0; i<_scenes.size(); i++)
            {
                IScene* scene = _scenes[i];
                if(scene) scene->OnKeyboard(key,x,y);
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
        static void Glut_Keyboard(unsigned char key, int x, int y)
        {
            return Get().Keyboard(key, x, y);
        }
    };
} // GLIZ
