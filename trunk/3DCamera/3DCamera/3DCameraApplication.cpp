#include "3DCameraApplication.h"
#include <stdio.h>

C3DCameraApplication::C3DCameraApplication(HDC &hDC, HWND &hWnd)
	: C3DApplication(hDC, hWnd)
{
	mpViewCamera = NULL;
}

C3DCameraApplication::~C3DCameraApplication(void)
{
	if (mpViewCamera != NULL)
	{
		delete mpViewCamera;
	}
	if (mpCamera != NULL)
	{
		delete mpCamera;
	}
}

void test()
{
	const float Z_STEP = 2;
	const float X_STEP = 2;

	CVector3f position = CVector3f();

	/*		|z+
			|
			|
	-x------+--------x+
			|
			|* <= (0,0,-2)
			|z-			*/
	position.z = -Z_STEP;
	float angle = position.angleToVector(CVector3f(0,-1,0));

	/*		|z+
			|
			|
	-x------+--------x+
			|
			|		* <= (2,0,-2)
			|z-			*/
	position.x = X_STEP;
	angle = position.angleToVector(CVector3f(0,0,-1));

	/*		|z+
			|
			|
	-x------+--------x+
			|		* <= (2,0,0)
			|		
			|z-			*/
	position.z = 0;
	angle = position.angleToVector(CVector3f(0,0,-1));

	/*		|z+
			|		* <= (2,0,2)
			|
	-x------+--------x+
			|		
			|		
			|z-			*/
	position.z = Z_STEP;
	angle = position.angleToVector(CVector3f(0,0,-1));

	/*		|z+
			|* <= (0,0,2)
			|
	-x------+--------x+
			|		
			|		
			|z-			*/
	position.x = 0;
	angle = position.angleToVector(CVector3f(0,0,-1));

	/*		|z+
		* <= (-2,0,2)
			|
	-x------+--------x+
			|		
			|		
			|z-			*/
	position.x = -X_STEP;
	angle = position.angleToVector(CVector3f(0,0,-1));
}

GLvoid C3DCameraApplication::initScene()
{
	test();
	CVector3f position = CVector3f(0,-1,-2);
	CVector3f lookAt = CVector3f(0,0,0);

	float angleX = position.angleToVector(CVector3f(1,0,0));
	float angleY = position.angleToVector(CVector3f(0,-1,0));
	float angleZ = position.angleToVector(CVector3f(0,0,1));

	position.y = 1;

	angleX = position.angleToVector(CVector3f(1,0,0));
	angleY = position.angleToVector(CVector3f(0,-1,0));
	angleZ = position.angleToVector(CVector3f(0,0,1));

	CVector3f v1 = CVector3f(2,-1,1);
	CVector3f v2 = CVector3f(-1,0,0);
	float a = v1.angleToVector(v2);


	mpViewCamera = new C3DCamera();
	mpViewCamera->translateX(-4);
	mpViewCamera->translateY(-1);
	mpViewCamera->translateZ(-4);
	mpViewCamera->rotateY(-45);

	mpCamera = new C3DCamera();
	mpCamera->translateX(-2);
	mpCamera->translateY(-1);
	mpCamera->translateZ(-3);

	mpCamera->lookAt(mLookAt);
}

GLvoid C3DCameraApplication::updateScene()
{
	const GLfloat translateSpeed = 2.f;
	const GLfloat rotateSpeed = 20.f;

	// Vorwärts rückwärts
	if (g_Keystate['S'] == TRUE)
	{
		mpCamera->translateZ((GLfloat)mTimeDiff /1000 * translateSpeed);
	}
	if (g_Keystate['W'] == TRUE)
	{
		mpCamera->translateZ((GLfloat)mTimeDiff /1000 * -translateSpeed);
	}
	// links rechts
	if (g_Keystate['D'] == TRUE)
	{
		mpCamera->translateX((GLfloat)mTimeDiff /1000 * translateSpeed);
	}
	if (g_Keystate['A'] == TRUE)
	{
		mpCamera->translateX((GLfloat)mTimeDiff /1000 * -translateSpeed);
	}
	// hoch runter
	if (g_Keystate['R'] == TRUE)
	{
		mpCamera->translateY((GLfloat)mTimeDiff /1000 * translateSpeed);
	}
	if (g_Keystate['F'] == TRUE)
	{
		mpCamera->translateY((GLfloat)mTimeDiff /1000 * -translateSpeed);
	}

	// Rotation um X-Achse
	if (g_Keystate[VK_DOWN] == TRUE)
	{
		mpCamera->rotateX((GLfloat)mTimeDiff /1000 * rotateSpeed);
	}
	if (g_Keystate[VK_UP] == TRUE)
	{
		mpCamera->rotateX((GLfloat)mTimeDiff /1000 * -rotateSpeed);
	}

	// Rotation um Y-Achse
	if (g_Keystate[VK_LEFT] == TRUE)
	{
		mpCamera->rotateY((GLfloat)mTimeDiff /1000 * rotateSpeed);
	}
	if (g_Keystate[VK_RIGHT] == TRUE)
	{
		mpCamera->rotateY((GLfloat)mTimeDiff /1000 * -rotateSpeed);
	}
	// Rotation um Z-Achse
	if (g_Keystate['E'] == TRUE)
	{
		mpCamera->rotateZ((GLfloat)mTimeDiff /1000 * rotateSpeed);
	}
	if (g_Keystate['Q'] == TRUE)
	{
		mpCamera->rotateZ((GLfloat)mTimeDiff /1000 * -rotateSpeed);
	}

	if (g_Keystate['Y'] == TRUE)
	{
		mLookAt.x += (GLfloat)mTimeDiff /1000 * translateSpeed;
	}
	if (g_Keystate['X'] == TRUE)
	{
		mLookAt.x -= (GLfloat)mTimeDiff /1000 * translateSpeed;
	}

	mpCamera->lookAt(mLookAt);
}

GLvoid C3DCameraApplication::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	static ULONG lastOutput = GetTickCount();

	if (GetTickCount() > (lastOutput + 1000))
	{
		char out[MAX_PATH];
		sprintf(out, "Position: x=%f y=%f z=%f\n", mpCamera->getPosition().x, mpCamera->getPosition().y, mpCamera->getPosition().z);
		OutputDebugString(out);
		sprintf(out, "Rotation: x=%f y=%f z=%f\n", mpCamera->getRotation().x, mpCamera->getRotation().y, mpCamera->getRotation().z);
		OutputDebugString(out);

		lastOutput = GetTickCount();
	}

	glRotatef(mpViewCamera->getRotation().x, 1,0,0);
	glRotatef(mpViewCamera->getRotation().y, 0,1,0);
	glRotatef(mpViewCamera->getRotation().z, 0,0,1);

	glTranslatef(mpViewCamera->getPosition().x, mpViewCamera->getPosition().y, mpViewCamera->getPosition().z);
	
	glPointSize(5.f);
	glBegin(GL_POINTS);
		glVertex3f(0,0,0);
	glEnd();

	mpCamera->render();

	glBegin(GL_LINES);
		// Rot = X
		glColor3f(1.f,0,0);
		glVertex3f( 0.f, 0, 0);
		glVertex3f( 2.f, 0, 0);

		// Grün = Y
		glColor3d(0,1.f,0);
		glVertex3f(0, 0.f, 0);
		glVertex3f(0, 2.f, 0);

		// Blau = Z
		glColor3d(0,0,1.f);
		glVertex3f(0, 0, 0.f);
		glVertex3f(0, 0, 2.f);
	glEnd();

	
}


