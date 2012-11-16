#include "MapApplication.h"

#include "3DMapSaver.h"
#include "3DMapLoader.h"

CMapApplication::CMapApplication(HDC &hDC, HWND &hWnd)
:C3DApplication(hDC, hWnd)
{
	distance = -20;
	mRefresh = false;
}

CMapApplication::~CMapApplication()
{

}

GLvoid CMapApplication::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0,0,distance);

	glRotatef(mRotation.x, 1, 0, 0);
	glRotatef(mRotation.y, 0, 1, 0);
	glRotatef(mRotation.z, 0, 0, 1);

	glPointSize(5);

	glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0,0,0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(-8,8, MAP_HEIGHT);
		glVertex3f(8,-8, MAP_HEIGHT);

		glVertex3f(-8,-8, MAP_HEIGHT);
		glVertex3f(8,8, MAP_HEIGHT);

		glVertex3f(-8,8, -MAP_HEIGHT);
		glVertex3f(8,-8, -MAP_HEIGHT);

		glVertex3f(-8,-8, -MAP_HEIGHT);
		glVertex3f(8,8, -MAP_HEIGHT);
	glEnd();

	mMap->render();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glColor4f(0.0f, 0.0f, 1.0f, 0.3f);
	
	const GLfloat scaleFactor = 4;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
		glVertex3f(-8.0f * scaleFactor, 8.0f * scaleFactor, 0);
		glVertex3f( 0.0f * scaleFactor, 8.0f * scaleFactor, 0);
		glVertex3f( 0.0f * scaleFactor, 0.0f * scaleFactor, 0);
		glVertex3f(-8.0f * scaleFactor, 0.0f * scaleFactor, 0);

		glVertex3f(0.0f * scaleFactor, 8.0f * scaleFactor, 0);
		glVertex3f(8.0f * scaleFactor, 8.0f * scaleFactor, 0);
		glVertex3f(8.0f * scaleFactor, 0.0f * scaleFactor, 0);
		glVertex3f(0.0f * scaleFactor, 0.0f * scaleFactor, 0);

		glVertex3f(-8.0f * scaleFactor, 0.0f * scaleFactor, 0);
		glVertex3f( 0.0f * scaleFactor, 0.0f * scaleFactor, 0);
		glVertex3f( 0.0f * scaleFactor,-8.0f * scaleFactor, 0);
		glVertex3f(-8.0f * scaleFactor,-8.0f * scaleFactor, 0);

		glVertex3f(0.0f * scaleFactor, 0.0f * scaleFactor, 0);
		glVertex3f(8.0f * scaleFactor, 0.0f * scaleFactor, 0);
		glVertex3f(8.0f * scaleFactor,-8.0f * scaleFactor, 0);
		glVertex3f(0.0f * scaleFactor,-8.0f * scaleFactor, 0);
	glEnd();

	
}

GLvoid CMapApplication::updateScene()
{
	if (g_Keystate['Q'] == TRUE)
	{
		mRotation.y += ROT_SPEED * (GLfloat)mTimeDiff /1000;
	}
	if (g_Keystate['E'] == TRUE)
	{
		mRotation.y -= ROT_SPEED * (GLfloat)mTimeDiff /1000;
	}

	if (g_Keystate['A'] == TRUE)
	{
		mRotation.z += ROT_SPEED * (GLfloat)mTimeDiff /1000;
	}
	if (g_Keystate['D'] == TRUE)
	{
		mRotation.z -= ROT_SPEED * (GLfloat)mTimeDiff /1000;
	}

	if (g_Keystate['W'] == TRUE)
	{
		mRotation.x += ROT_SPEED * (GLfloat)mTimeDiff /1000;
	}
	if (g_Keystate['S'] == TRUE)
	{
		mRotation.x -= ROT_SPEED * (GLfloat)mTimeDiff /1000;
	}

	if (g_Keystate[VK_UP] == TRUE)
	{
		distance += ZOOM_SPEED * (GLfloat)mTimeDiff /1000;
	}
	if (g_Keystate[VK_DOWN] == TRUE)
	{
		distance -= ZOOM_SPEED * (GLfloat)mTimeDiff /1000;
	}

	if ((g_Keystate['R'] == TRUE) && (mRefresh == false))
	{
		mRefresh = true;

		delete mMap;
		CRandomFractal3DMapGenerator gen;
		mMap = gen.generateMap(MAP_SIZE, 16, 16, MAP_HEIGHT);
	}

	if ((g_Keystate['K'] == TRUE) && (mRefresh == false))
	{
		mRefresh = true;

		Sleep(1000);

		C3DMapSaver saver;
		if (saver.saveMap(mMap, "test.mff") == FALSE)
		{
			OutputDebugString("Fehler beim Speichern");
		}
	}

	if ((g_Keystate['L'] == TRUE) && (mRefresh == false))
	{
		mRefresh = true;

		Sleep(1000);

		C3DMapLoader loader;
		C3DMap* newMap = NULL;
		if (loader.loadMap("test.mff", newMap) == TRUE)
		{
			delete mMap;
			mMap = newMap;
		}
		else
		{
			OutputDebugString("Fehler beim Laden");
		}
	}

	if ((g_Keystate['R'] == FALSE) || (g_Keystate['K'] == FALSE) || (g_Keystate['L'] == FALSE))
	{
		mRefresh = false;
	}
}

GLvoid CMapApplication::initScene()
{
	CRandomFractal3DMapGenerator generator;

	mMap = generator.generateMap(MAP_SIZE, 16, 16, MAP_HEIGHT);
	
	C3DMapSaver saver;
	C3DMapLoader loader;
	//saver.saveMap(mMap, "test.mff");
	//loader.loadMap("test.mff", mMap);


	//C3DMap map(4, 4, 8, 8);
}
