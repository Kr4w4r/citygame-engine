#ifndef MAP_APPLICATION_H
#define MAP_APPLICATOIN_H

#include "3DApplication.h"
#include "RandomFractal3DMapGenerator.h"

const GLfloat ROT_SPEED = 20.0f;
const GLfloat ZOOM_SPEED = 5.0f;

const GLfloat MAP_HEIGHT = 3.0f;

const GLuint MAP_SIZE = 512;

class CMapApplication : public C3DApplication
{
public:
	CMapApplication(HDC &hDC, HWND &hWnd);
	virtual ~CMapApplication();
	
protected:
	CVector3f mRotation;
	GLfloat distance;

	bool mRefresh;

	C3DMap* mMap;

	virtual GLvoid drawScene();
	virtual GLvoid updateScene();
	virtual GLvoid initScene();
};

#endif
