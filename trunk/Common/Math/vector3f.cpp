#include "vector3f.h"

CVector3f::CVector3f()
{
	x = 0;
	y = 0;
	z = 0;
}

CVector3f::CVector3f(GLfloat X, GLfloat Y, GLfloat Z)
{
	x = X;
	y = Y;
	z = Z;
}

CVector3f::~CVector3f()
{}

GLvoid CVector3f::set(GLfloat X, GLfloat Y, GLfloat Z)
{
	x = X;
	y = Y;
	z = Z;
}

GLvoid CVector3f::normalize()
{
	GLfloat len = length();
	if (len != 0)
	{
		 x /= len;
		 y /= len;
		 z /= len;
	}
}

GLfloat CVector3f::length()
{
	// hier gegebenenfalls SIMD per SSE verwenden (siehe Buch 
	// 3D-Spiele-Programmierung(Raumschiff auf dem Cover) S.147)
	return sqrtf(x*x + y*y + z*z);
}

GLfloat CVector3f::angleToVector(CVector3f v)
{
	// vor teilen durch 0 schützen
	GLfloat vectorLengths = length() * v.length();
	if (vectorLengths != 0)
	{
		GLfloat param = ((x*v.x + y*v.y + z*v.z) / vectorLengths);
		return (GLfloat)(acos(param) * 180 / M_PI );
	}
	return 0;
}

CVector3f CVector3f::operator +(const CVector3f v)
{
	return CVector3f(x + v.x, y + v.y, z + v.z); 
}

CVector3f CVector3f::operator-(const CVector3f v)
{
	return CVector3f(x - v.x, y - v.y, z - v.z);
}
CVector3f CVector3f::operator*(const GLfloat factor)
{
	return CVector3f(x * factor, y * factor, z * factor);
}

CVector3f CVector3f::operator*(const CVector3f v)
{
	return CVector3f(x * v.x, y * v.y, z * v.z);
}

GLvoid CVector3f::operator+=(const CVector3f v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

GLvoid CVector3f::operator-=(const CVector3f v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

GLvoid CVector3f::operator*=(const GLfloat factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
}

CVector3f CVector3f::crossProduct(const CVector3f v)
{
	return CVector3f(	y*v.z - z*v.y, 
						z*v.x - x*v.z,
						x*v.y - y*v.x);
}