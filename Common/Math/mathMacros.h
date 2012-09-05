#ifndef MATH_MACROS_H
#define MATH_MACROS_H

#define _USE_MATH_DEFINES
#include <math.h>

#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))

#define DEG(angle) (float)(angle*(M_PI/180))

#endif