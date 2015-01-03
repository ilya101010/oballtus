#pragma once
#include "libs.h"

namespace GLIZ
{
    class TimeLine
    {
    public:
        typedef long long unsigned int Time;
        inline static double ToSeconds() { return 1.0/1000; }
    private:
        bool started;
        Time t;
        clock_t ticks;
    private:
        TimeLine() : t(0), ticks(0), started(false) { Start(); }
        inline static TimeLine& Instance()
        {
            static TimeLine tl;
            return tl;
        }
    private:
        inline Time GetDt()
        {
            clock_t curTicks = ticks;
            ticks = clock();
            Time dt = (ticks-curTicks) * 1000 / CLOCKS_PER_SEC;
            t += dt;
            return dt;
        }
        inline Time GetCurrentTime() // in msec
        {
            return t;
        }
    private:
        inline void Start() { t = 0; ticks = 0; started = true; } // if we start from 0
        inline void Stop() { started = false; }
    public:
        inline static Time Dt() {return TimeLine::Instance().GetDt();}
        //inline static void Dt(long long unsigned dt);
    };
}
