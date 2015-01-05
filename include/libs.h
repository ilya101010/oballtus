#pragma once

// standard libraries
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cstdio>
#include <vector>
#include <utility>
#include <unistd.h>
#include <time.h>

// GL
#include <GL/gl.h>
#include <GL/glu.h>

#ifdef _MINGW32_
#include <windows.h>
#include <GL/freeglut.h>
#endif

#ifdef linux
#include <GL/glut.h>
#endif

// using
using namespace std;

// Defines

// Constants
const double C_TMS = 42; // Timer Milliseconds