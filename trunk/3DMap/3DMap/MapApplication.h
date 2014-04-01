#ifndef MAP_APPLICATION_H
#define MAP_APPLICATOIN_H

#include "3DApplication.h"
#include "RandomFractal3DMapGenerator.h"
#include "IOHandlerThread.h"
#include "MapApplicationKeyBindings.h"
#include "3DMapLevelOfDetailRenderer.h"

const GLfloat ROT_SPEED = 20.0f;
const GLfloat ZOOM_SPEED = 5.0f;

const GLfloat MOVE_SPEED = 1.0f;

const GLfloat MAP_HEIGHT = 3.0f;

const GLuint MAP_SIZE = 512 * 2;
const UCHAR LOD_DEPTH = 4;

class CMapApplication : public C3DApplication
{
public:
	CMapApplication(HDC &hDC, HWND &hWnd);
	virtual ~CMapApplication();
	
protected:
	CVector3f mRotation;
	GLfloat distance;
	CVector3f mFakeCamPos;

	bool mRefresh;

	C3DMapData* mMap;

	virtual GLvoid drawScene();
	virtual GLvoid updateScene();
	virtual GLvoid initScene();

	CIOHandlerThread mIOHandlerThread;
	CMapApplicationKeyBindings mKeyBindings;

	C3DMapLevelOfDetailRenderer* mpRenderer;
};

#endif
