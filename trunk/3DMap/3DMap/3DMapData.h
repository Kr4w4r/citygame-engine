#ifndef _3DMAP_H
#define _3DMAP_H

#define WIN32_LEAN_AND_MEAN

#include "IMap.h"

class C3DMapData : public IMap
{
public:
	C3DMapData(GLuint horizontalCellCount, GLuint verticalCellCount, GLfloat maxHeight);
	C3DMapData(GLuint horizontalCellCount, GLuint verticalCellCount, GLfloat width, GLfloat height, GLfloat maxHeight);
	C3DMapData(GLuint horizontalCellCount, GLuint verticalCellCount, MAP_DATA mapData);
	~C3DMapData();

	void render();

	GLuint getWidth();
	GLuint getHeight();

	GLfloat getMaxHeight() { return mMaxHeight; };

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