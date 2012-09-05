#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define _USE_MATH_DEFINES 
#include <math.h>	// für M_PI, sin, cos

typedef enum {
	PLANE_X_Y,
	PLANE_Y_X,

	PLANE_X_Z,
	PLANE_Z_X,

	PLANE_Y_Z,
	PLANE_Z_Y
} E_PLANE;

class CVector3f
{
public:
	CVector3f();
	CVector3f(GLfloat x, GLfloat y, GLfloat z);
	~CVector3f();

	GLvoid set(GLfloat x, GLfloat y, GLfloat z);

	GLvoid normalize();
	GLfloat length();
	GLfloat angleToVector(CVector3f v);
	GLfloat angleToPlane(E_PLANE plane);

	// Operatoren
	CVector3f operator+(const CVector3f v);
	CVector3f operator-(const CVector3f v);
	CVector3f operator*(const CVector3f v);
	CVector3f operator*(const GLfloat factor);

	GLvoid operator+=(const CVector3f v);
	GLvoid operator-=(const CVector3f v);
	GLvoid operator*=(const GLfloat factor);

	CVector3f crossProduct(const CVector3f v);

	// public Variables
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

#endif