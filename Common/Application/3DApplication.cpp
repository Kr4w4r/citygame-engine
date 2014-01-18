#include "3DApplication.h"
#include "EventManager.h"
#include "TickEvent.h"

#include <stdio.h>
#include "EventManager.h"

C3DApplication::C3DApplication(HDC& hDC, HWND &hWnd) :
mhDC(hDC),
mhWnd(hWnd)
{
	mLastTime = GetTickCount();
	mLastCaptionUpdate = GetTickCount();

	mInitialized = FALSE;
}

C3DApplication::~C3DApplication()
{
	
}

BOOLEAN C3DApplication::enter()
{
	ULONG now = GetTickCount();
	mTimeDiff = now - mLastTime;
	mLastTime = now;

	CEventManager::getInstance()->queueEvent(new CTickEvent(mTimeDiff));

	if (mInitialized == FALSE)
	{
		initScene();
		mInitialized = TRUE;
	}

	if (now - mLastCaptionUpdate > 500)
	{
		char caption[64];
		sprintf_s(caption, 64, "FPS: %f", 1000/(GLfloat)mTimeDiff);
		SetWindowText(mhWnd, caption);

		mLastCaptionUpdate = now;
	}

	updateScene();
	drawScene();
	return TRUE;
}

BOOLEAN C3DApplication::initGL(GLsizei width, GLsizei height)
{
	establishProjectionMatrix(width, height);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

	if (glIsEnabled(GL_POLYGON_SMOOTH) == GL_TRUE)
	{
		glEnable(GL_POLYGON_SMOOTH);
	}

	return TRUE;
}

GLvoid C3DApplication::establishProjectionMatrix(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		return;
	}

	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	GLfloat distance = 7;
	GLfloat sideDistance =  width / distance;
	GLfloat heightDistance = (height / sideDistance);

	// für 2D
	//glOrtho(-distance, distance, -heightDistance, heightDistance, 0.1f, 200.0f);
	// für 3D
	gluPerspective(45.f, (GLfloat)width / (GLfloat)height, 0.1f, 200.f); 

	mWidth = width;
	mHeight = height;
}

GLvoid C3DApplication::initScene()
{
	// im normalfall passiert hier nichts
}