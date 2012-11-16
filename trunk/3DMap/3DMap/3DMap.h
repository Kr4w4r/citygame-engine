#ifndef _3DMAP_H
#define _3DMAP_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "GL/gl.h"
#include "GL/glu.h"

#include "Vector3f.h"

typedef CVector3f MAP_CORNER;
typedef MAP_CORNER*** MAP_DATA;

class C3DMap
{
public:
	C3DMap(GLuint horizontalCellCount, GLuint verticalCellCount, GLfloat maxHeight);
	C3DMap(GLuint horizontalCellCount, GLuint verticalCellCount, GLfloat width, GLfloat height, GLfloat maxHeight);
	C3DMap(GLuint horizontalCellCount, GLuint verticalCellCount, MAP_DATA mapData);
	~C3DMap();

	void render();

	GLuint getWidth();
	GLuint getHeight();

	MAP_CORNER* getMapCorner(GLuint x, GLuint y);

private:
	void generateFlatMap(GLuint gridWidth, GLuint gridHeight, GLfloat width, GLfloat height);
	CVector3f getColor(GLfloat height);

protected:
	GLuint mWidth;
	GLuint mHeight;
	GLfloat mMaxHeight;

	// 2D Array auf ein MAP_CORNER*
	MAP_DATA mMapData;
};

#endif