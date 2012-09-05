#ifndef VECTOR2F_H
#define VECTOR2F_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define _USE_MATH_DEFINES 
#include <math.h>	// für M_PI, sin, cos

class CVector2f
{
public:
	CVector2f();
	CVector2f(GLfloat x, GLfloat y);
//	CVector2f&(CVector& vector);

	VOID normalize();

	GLfloat length();
	GLfloat angleTo(CVector2f vec);

	GLfloat x;
	GLfloat y;
};

#endif