#include "vector2f.h"

CVector2f::CVector2f()
{
	x = 0;
	y = 0;
}

CVector2f::CVector2f(GLfloat _x, GLfloat _y)
{
	x = _x;
	y = _y;
}

/*
CVector2f::CVector2f(CVector2f& vector)
{
	x = vector.x;
	y = vector.y;
}
*/
GLfloat CVector2f::length()
{
	// hier gegebenenfalls SIMD per SSE verwenden (siehe Buch 
	// 3D-Spiele-Programmierung(Raumschiff auf dem Cover) S.147)
	return sqrtf(x*x + y*y);
}

GLfloat CVector2f::angleTo(CVector2f vec)
{
	// vor teilen durch 0 schützen
	GLfloat vectorLengths = length() * vec.length();
	if (vectorLengths != 0)
	{
		GLfloat param = ((x*vec.x + y*vec.y) / vectorLengths);
		return (GLfloat)(acos(param) * 180 / M_PI );
	}
	return 0;
}

VOID CVector2f::normalize()
{
	GLfloat len = length();
	if (len != 0)
	{
		 x /= len;
		 y /= len;
	}
}