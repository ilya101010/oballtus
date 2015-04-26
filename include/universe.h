#pragma once
#include "libs.h"
#include "dot.h"
#include "object.h"
#include "collision.h"
#include "ball.h"
#include "borders.h"
#include "timeline.h"
#include "text.h"
#include "line.h"

namespace GLIZ
{
    class IUniverse
    {
    public:
        vector<Object*> objects;
        void Add(Object* obj)
        {
            objects.push_back(obj);
        }

        void Draw()
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            for(int i = 0; i<objects.size(); i++)
            {
                glColor4f(1,1,1,1);
                if(objects[i] && objects[i]->element->drawable) objects[i]->element->DrawGL();
            }
        }

        virtual void MoveObjects()=0;
        virtual void OnClick(double x, double y)=0;
        virtual void OnKeyboard(unsigned char key, int x, int y)=0;
        //virtual void OnKeyboard(double )
    };

    /* class MyUniverse : public IUniverse, public CollisionManager
    {
        bool editmode;
        bool dotmode;
    public:
        inline Borders& borders()
        {
            return *(static_cast<Borders*>(objects[1]));
        }
        inline Ball& ball()
        {
            return *(static_cast<Ball*>(objects[0]));
        }

        MyUniverse()
        {
            editmode = dotmode =false;

            Object *obj = new Ball(); Add(obj);
            Borders *bor = new Borders(); ifstream f("test");
            bor->Read(f);
            Add(bor); // 1
            ball().sphere().r=borders().BallR(); ball().sphere().c.z=0;
            // edit mode
            Object *bg = new Object();
                Quad *q = new Quad(); q->drawable=false;
                q->a = Dot(-1,1,-1);q->b=Dot(1,1,-1);q->c=Dot(1,-1,-1);q->d=Dot(-1,-1,-1);
                q->bl=1; q->r=0.75; q->g=0.5; q->al=0.5;
                bg->element=q;
            Add(bg); // 2
            Object *tt = new Object();
                TextEl *t = new TextEl("Editing mode"); tt->element=t; tt->element->drawable=false;
            Object *tt1 = new Object();
                TextEl *t1 = new TextEl("Place dots by clicking"); tt1->element=t1; tt1->element->drawable=false;
            Add(tt); // 3
            Add(tt1); // 4
        }
        ~MyUniverse() {}

        void OnClick(double x, double y)
        {
            if(dotmode)
            {
                return;
            }
            Dot c = ball().sphere().c;
            Vec vv = (Vec(x,y)-c);
            Vec v = vv.normalize(0.02);
            ball().v=v;
        }

        void OnKeyboard(unsigned char key, int x, int y)
        {
            if(key == 'e' || key == 'E')
            {
                objects[2]->element->drawable=!objects[2]->element->drawable;
                objects[3]->element->drawable=!objects[3]->element->drawable;
                editmode = !editmode;
            }
            if(editmode && (key == 'd' || key == 'D'))
            {
                objects[3]->element->drawable=!objects[3]->element->drawable;
                objects[4]->element->drawable=!objects[4]->element->drawable;
                ball().Movable = !ball().Movable;
                dotmode = !dotmode;
            }
        }

        void MoveObjects()
        {
            int dt = C_TMS;
            // moving things
            for(int i=0; i<objects.size(); i++)
                objects[i]->Move(dt);
            // colliding things
            bool fCollision = false;
            for(int i = 0; i<borders().model().elements.size(); i++)
            {
                Quad q = borders().quad(i);
                Line* rl = ReflectLine(&ball().sphere(),&q, true); // only edges!
                if(rl != NULL)
                    if (normal(*rl)*ball().v < 0)
                    { ball().v = Reflect(ball().v,{rl->first,rl->second}), cout << "yeah"; fCollision = true; break; }
            }
            if (!fCollision)
                for(int i = 0; i<borders().model().elements.size(); i++)
                {
                    Quad q = borders().quad(i);
                    Line* rl = ReflectLine(&ball().sphere(),&q); // only edges!
                    if(rl != NULL)
                        if (normal(*rl)*ball().v < 0)
                        {
                            ball().v = Reflect(ball().v,{rl->first,rl->second});
                            cout << "yeah"; break;
                        }
                }
            // reacting things (just do nothing!)
            for(int i = 0; i<objects.size(); i++)
                objects[i]->React();
        }
    }; */

    /*
     class MyUniverse : public IUniverse, public CollisionManager
    {
        bool editmode = false;
        bool dotmode;
    public:
        inline PolyChain& pc()
        {
            return *(static_cast<PolyChain*>(objects[0]));
        }
        inline Ball& ball()
        {
            return *(static_cast<Ball*>(objects[1]));
        }
        MyUniverse()
        {
            PolyChain *p = new PolyChain();
            p->AddLine(Line(Dot(0,0),Dot(0,1)));
            Add(p); // 0
            Object *obj = new Ball(); Add(obj); // 1
            ball().sphere().r=0.05;
            ball().sphere().c=Dot(-0.5,-0.5);
            ball().Movable=true;
        }
        ~MyUniverse() {}

        void OnClick(double x, double y)
        {
            if (editmode) pc().AddDot(Dot(x,y));
            else
            {
                Dot c = ball().sphere().c;
                Vec vv = (Vec(x,y)-c);
                Vec v = vv.normalize(0.02);
                ball().v=v;
            }
        }

        void OnKeyboard(unsigned char key, int x, int y)
        {
            if(key == 'e' || key == 'E') editmode = !editmode;
        }

        void MoveObjects()
        {
            int dt = C_TMS;
            // moving things
            for(int i=0; i<objects.size(); i++)
                objects[i]->Move(dt);
            for(int i = 0; i<objects.size(); i++)
                objects[i]->React();
            for(int i = 0; i<pc().model().elements.size(); i++)
            {
                Line t = pc().line(i).ToLine();
                bool a = CollisionManager::Intersection(t,&ball().sphere());
                if(i == pc().model().elements.size()-1)
                    if(a) { ball().v=Reflect(ball().v,t); break; }
                /* Line d = pc().line(i+1).ToLine();
                bool b = CollisionManager::Intersection(d,&ball().sphere());
                if (a && b)
                {
                    Dot ad = t.second;
                    Line a = Line(ball().sphere().c, ad);
                    Vec n = normal(a);
                    Line l = make_pair(ad, ad+n);
                    ball().v=Reflect(ball().v,l);
                }
            }
        }
    }; */
    class MyUniverse : public IUniverse, public CollisionManager
    {
    public:
        enum submode {NONE, EDIT, DOT, SETTINGS, OUTPUT};
        bool editmode;
        submode S;
        Quad tmp;
        inline Ball& ball()
        {
            return *(static_cast<Ball*>(objects[0]));
        }
        inline Model& model()
        {
            return *(static_cast<Model*>(objects[1]->element));
        }
        inline Quad& quad(int i)
        {
            return *(static_cast<Quad*>(model().elements[i]));
        }
        MyUniverse()
        {
            Object *oball = new Ball(); Add(oball); ball().sphere().r = 0.01;
            Object *walls = new Object(); walls->element=new Model(); Add(walls);
            tmp = Quad(Dot(NULL,NULL),Dot(NULL,NULL),Dot(NULL,NULL),Dot(NULL,NULL));
            Object *bg = new Object();
                Quad *q = new Quad(); q->drawable=false;
                q->a = Dot(-1,1,-1);q->b=Dot(1,1,-1);q->c=Dot(1,-1,-1);q->d=Dot(-1,-1,-1);
                q->bl=1; q->r=0.75; q->g=0.5; q->al=0.5;
                bg->element=q;
                Add(bg); // 2
             Object *maint = new Object(); Model *editText = new Model();
                TextEl *t0 = new TextEl("Editing mode"); editText->elements.push_back(t0);
                TextEl *t1 = new TextEl("[d] - enter dot-mode"); t1->c.y=t0->c.y-0.05; editText->elements.push_back(t1); t1->font=GLUT_BITMAP_HELVETICA_12;
                TextEl *t2 = new TextEl("[s] - enter settings"); t2->c.y=t1->c.y-0.03; editText->elements.push_back(t2); t2->font=GLUT_BITMAP_HELVETICA_12;
                TextEl *t3 = new TextEl("[o] - output to model.oba"); t3->c.y=t2->c.y-0.03; editText->elements.push_back(t3); t3->font=GLUT_BITMAP_HELVETICA_12;
            maint->element=editText; maint->element->drawable=false; Add(maint); // 3
            Object *dott = new Object(); TextEl *dotText = new TextEl("Dot-mode"); dott->element=dotText; dott->element->drawable=false; Add(dott); // 4
            //Object *demo = new Object(); TextEl2 *demon = new TextEl2(); demo->element=demon; Add(demo);
        }
        ~MyUniverse() {}

        void OnClick(double x, double y)
        {
            if(S == DOT)
            {
                Dot a = Dot(x,y);
                Dot on(NULL,NULL);
                if(tmp.a == on)
                    tmp.a = a;
                else if(tmp.b == on)
                    tmp.b = a;
                else if(tmp.c == on)
                    tmp.c = a;
                else if(tmp.d == on)
                {
                    tmp.d = a;
                    Object* tada = new Object();
                    Quad *tmp1 = new Quad(tmp.a,tmp.b,tmp.c,tmp.d);
                    if(tmp1->Clockwise()) tmp1->Revert();
                    model().elements.push_back(tmp1);
                    tmp = Quad(Dot(NULL,NULL),Dot(NULL,NULL),Dot(NULL,NULL),Dot(NULL,NULL));
                }
            }
            else
            {
                Dot c = ball().sphere().c;
                Vec vv = (Vec(x,y)-c);
                Vec v = vv.normalize(0.02);
                ball().v=v;
            }
        }

        void Output()
        {
            ofstream o("model.oba");
            o << "!oballtus-model" << endl;
            o << "model (" << model().elements.size() <<" elements) {" << endl;
            for(int i = 0; i<model().elements.size(); i++)
                o << quad(i) << endl;
            o << "}";
        }

        void OnKeyboard(unsigned char key, int x, int y)
        {
            if(!editmode) // none
            {
                if(key == 'E' || key == 'e') // turn on edit-mode
                {
                    editmode=true;
                    objects[2]->element->drawable=true;
                    objects[3]->element->drawable=true;
                }
            }
            else if (editmode && S < DOT) // edit-mode
            {
                if(key == 'E' || key == 'e') // exit
                {
                    editmode = false;
                    objects[2]->element->drawable=false;
                    objects[3]->element->drawable=false;
                }
                else if (key == 'd' || key == 'D') // enter dot-mode
                {
                    S = DOT;
                    objects[3]->element->drawable=false;
                    objects[4]->element->drawable=true;
                }
                else if (key == 's' || key == 'S') // enter setting-mode
                {
                    cout << "ERROR: Settings mode hasn't been implemented yet." << endl;
                }
                else if (key == 'o' || key == 'O') // output
                {
                    Output();
                    cout << "The output to model.oba is finished." << endl;
                }
            }
            else if(editmode && S == DOT)
            {
                if (key == 'd' || key == 'D') // exit
                {
                    S = EDIT;
                    objects[3]->element->drawable=true;
                    objects[4]->element->drawable=false;
                }
            }
        }

        void MoveObjects()
        {
            if(!editmode)
            {
                int dt = C_TMS;
                for (int i = 0; i < objects.size(); i++)
                    objects[i]->Move(dt);
                bool fCollision = false;
                for (int i = 0; i < model().elements.size(); i++) {
                    Quad q = quad(i);
                    Line *rl = ReflectLine(&ball().sphere(), &q, true);
                    if (rl != NULL) if (normal(*rl) * ball().v < 0) {
                        ball().v = Reflect(ball().v, {rl->first, rl->second}), cout << "yeah";
                        fCollision = true;
                        break;
                    }
                }
                for (int i = 0; i < objects.size(); i++)
                    objects[i]->React();
            }
        }
    };
}