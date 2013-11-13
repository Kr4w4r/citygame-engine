#include "3DCameraApplication.h"
#include <stdio.h>

C3DCameraApplication::C3DCameraApplication(HDC &hDC, HWND &hWnd)
	: C3DApplication(hDC, hWnd)
{
	mpCamera = NULL;
}

C3DCameraApplication::~C3DCameraApplication(void)
{
	if (mpCamera != NULL)
	{
		delete mpCamera;
	}
}

GLvoid C3DCameraApplication::initScene()
{
	mpCamera = new C3DCamera();
}

GLvoid C3DCameraApplication::updateScene()
{
	const GLfloat translateSpeed = 2.f;
	const GLfloat rotateSpeed = 20.f;

	// Vorwärts rückwärts
	if (g_Keystate['W'] == true)
	{
		mpCamera->translateZ((GLfloat)mTimeDiff /1000 * translateSpeed);
	}
	if (g_Keystate['S'] == true)
	{
		mpCamera->translateZ((GLfloat)mTimeDiff /1000 * -translateSpeed);
	}

	// Rotation um X-Achse
	if (g_Keystate[VK_UP] == true)
	{
		mpCamera->rotateX((GLfloat)mTimeDiff /1000 * rotateSpeed);
	}
	if (g_Keystate[VK_DOWN] == true)
	{
		mpCamera->rotateX((GLfloat)mTimeDiff /1000 * -rotateSpeed);
	}

	// Rotation um Y-Achse
	if (g_Keystate[VK_LEFT] == true)
	{
		mpCamera->rotateY((GLfloat)mTimeDiff /1000 * rotateSpeed);
	}
	if (g_Keystate[VK_RIGHT] == true)
	{
		mpCamera->rotateY((GLfloat)mTimeDiff /1000 * -rotateSpeed);
	}
	// Rotation um Z-Achse
	if (g_Keystate['E'] == true)
	{
		mpCamera->rotateZ((GLfloat)mTimeDiff /1000 * rotateSpeed);
	}
	if (g_Keystate['Q'] == true)
	{
		mpCamera->rotateZ((GLfloat)mTimeDiff /1000 * -rotateSpeed);
	}
}

GLvoid C3DCameraApplication::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(mpCamera->getPosition().x, mpCamera->getPosition().y, mpCamera->getPosition().z);

	char out[MAX_PATH];
	sprintf(out, "Rotation: x=%f y=%f z=%f\n", mpCamera->getRotation().x, mpCamera->getRotation().y, mpCamera->getRotation().z);
	OutputDebugString(out);

	glRotatef(mpCamera->getRotation().x, 1,0,0);
	glRotatef(mpCamera->getRotation().y, 0,1,0);
	glRotatef(mpCamera->getRotation().z, 0,0,1);
	
	glPointSize(5.f);
	glBegin(GL_POINTS);
		glVertex3f(0,0,0);
	glEnd();


	glBegin(GL_LINES);
		// Rot = X
		glColor3f(1.f,0,0);
		glVertex3f(-2.f, 0, 0);
		glVertex3f( 2.f, 0, 0);

		// Grün = Y
		glColor3d(0,1.f,0);
		glVertex3f(0,-2.f, 0);
		glVertex3f(0, 2.f, 0);

		// Blau = Z
		glColor3d(0,0,1.f);
		glVertex3f(0, 0,-2.f);
		glVertex3f(0, 0, 2.f);
	glEnd();
}


