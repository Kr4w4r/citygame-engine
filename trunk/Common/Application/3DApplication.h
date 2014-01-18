#ifndef _3D_APPLICATION_H
#define _3D_APPLICATION_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

extern BOOLEAN g_Keystate[256];

const GLsizei windowWidth = 800;
const GLsizei windowHeight = 600;
const GLsizei windowBits = 32;

/*****************************************************************

	@class C3DApplication
	@brief Einstiegsklasse in das Programm

*****************************************************************/
class C3DApplication
{
public:
	C3DApplication(HDC &hDC, HWND &hWnd);
	virtual ~C3DApplication();

	virtual BOOLEAN enter();
	virtual BOOLEAN initGL(GLsizei width, GLsizei height);
	virtual GLvoid establishProjectionMatrix(GLsizei width, GLsizei height);

protected:
	virtual GLvoid drawScene() = 0;
	virtual GLvoid updateScene() = 0;
	virtual GLvoid initScene();

protected:
	HDC &mhDC;
	HWND &mhWnd;

	GLsizei mWidth;
	GLsizei mHeight;

	ULONG	mTimeDiff;
	ULONG	mLastTime;
	ULONG	mLastCaptionUpdate;

	BOOLEAN mInitialized;
};

#endif