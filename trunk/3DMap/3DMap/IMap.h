#pragma once

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "GL/gl.h"
#include "GL/glu.h"

#include "Vector3f.h"

typedef CVector3f MAP_CORNER;
typedef MAP_CORNER*** MAP_DATA;

__interface IMap
{
	GLuint getWidth();
	GLuint getHeight();
	GLfloat getMaxHeight();

	MAP_CORNER* getMapCorner(GLuint x, GLuint y);
};