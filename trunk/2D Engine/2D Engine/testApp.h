#ifndef TEST_APP_H
#define TEST_APP_H

#include "2dApplication.h"
#include "ImageManager.h"
#include "PlayerSprite.h"
#include "Map2D.h"
#include "CollisionObjectList.h"
#include "Camera.h"

#include "EventManager.h"

#include "TestThread.h"

#include "MD2Loader.h"

// Globale Instanz des ImageManagers erzeugen
CImageManager gImageManager;

const GLfloat CAM_SPEED = 1.2f;
const ULONG KEY_DELAY = 200;

class CTestApp : public C2DApplication
{
public:
	CTestApp(HDC &hDC, HWND &hWnd) : C2DApplication(hDC, hWnd) {};
	~CTestApp() 
	{
		delete mPlayer;
		delete mPlayer2;
		delete mpMap;
		delete mpCamera;
	};

protected:

	typedef map<E_ANIMATION_TYPE, CTextureAnimation*> _ANIMATION_MAP;
	typedef _ANIMATION_MAP::value_type _ANIMATION_MAP_VALUE;
	typedef _ANIMATION_MAP::iterator _ANIMATION_MAP_ITER;
	_ANIMATION_MAP mAnimations;

	GLvoid testEventSystem()
	{
		CEventListener listener;
		CEventListener listener2;
		CEventManager::getInstance()->addEventListener(&listener, EVENT_MOUSE_CLICK);
		CEventManager::getInstance()->addEventListener(&listener2, EVENT_MOUSE_CLICK);

		CEventManager::getInstance()->addEventListener(&listener, EVENT_KEYBOARD_KEY_DOWN);
//		CEventManager::getInstance()->deleteEventListener(
	}

	virtual GLvoid initScene()
	{
		CMD2Loader md2Loader;
		md2Loader.loadMD2("C:\\Users\\Arne\\Desktop\\Neuer Ordner\\test.md2");

		testEventSystem();
		mpCamera = new CCamera(0,0, mWidth, mHeight);

		mpMap = new CMap2D(10, 10, 2.0f);

		CTexture* texture;
		gImageManager.getImage(IMAGE_TREE_TILE, texture);
		
		CTile* pTile;
		mpMap->getTile(3, 3, pTile);
		pTile->setTexture(texture);
		mpMap->getTile(3, 4, pTile);
		pTile->setTexture(texture);
		mpMap->getTile(3, 5, pTile);
		pTile->setTexture(texture);
		mpMap->getTile(4, 5, pTile);
		pTile->setTexture(texture);
		mpMap->getTile(4, 4, pTile);
		pTile->setTexture(texture);

		gImageManager.getImage(IMAGE_COLOR_TEST, texture);
		mpMap->setTile(0, 0, false, texture);
		
		gImageManager.getImage(IMAGE_MAN_STAND, texture);
		GLfloat ratio = (GLfloat)texture->getWidth() / (GLfloat)texture->getHeight();
		mPlayer = new CPlayerSprite(0, 0, ratio, 1, texture);

		gImageManager.getImage(IMAGE_COLOR_TEST, texture);
		mPlayer2 = new CPlayerSprite(3, 2, ratio, 1, texture);

		dir = true;
	};

	virtual GLvoid drawScene() 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(-mpCamera->getPosition().x, -mpCamera->getPosition().y, -4.f);

		char out[200];
		sprintf(out, "camPos: x=%f y=%f\n", mpCamera->getPosition().x, mpCamera->getPosition().y);
		//OutputDebugString(out);

		mpMap->render();
		mPlayer->render();

		mPlayer2->render();
		
	};

	virtual GLvoid updateScene() 
	{
		processPlayerInput();
		processCameraInput();

		testMouseCoordinates();
	};

	void testMouseCoordinates()
	{
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport); //(X, Y, Width, Height)

		GLdouble modelviewMatrix[16]; // 4x4 Matrix
		glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);

		GLdouble projectionMatrix[16];
		glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);

		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(mhWnd, &mousePos);

		GLfloat fWinX = mousePos.x;
		GLfloat fWinY = (GLfloat)viewport[3] - mousePos.y;
		GLfloat fWinZ = 0.0f;

		// Z-Koordinate ermitteln
		glReadPixels(fWinX, fWinY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &fWinZ);

		GLdouble worldCoordinateX, worldCoordinateY, worldCoordinateZ;
		gluUnProject(fWinX, fWinY, fWinZ, modelviewMatrix, projectionMatrix, viewport, &worldCoordinateX, &worldCoordinateY, &worldCoordinateZ);

		CHAR output[200];
		sprintf(output, "Mouse: X=%f Y=%f Z=%f", worldCoordinateX, worldCoordinateY, worldCoordinateZ);
		//OutputDebugString(output);
	}

	void processCameraInput()
	{
		/*
		if (g_Keystate['W'] == TRUE)
		{
			mCamPos.y -= CAM_SPEED * (GLfloat)mTimeDiff /1000;
		}
		if (g_Keystate['S'] == TRUE)
		{
			mCamPos.y += CAM_SPEED * (GLfloat)mTimeDiff /1000;
		}
		if (g_Keystate['A'] == TRUE)
		{
			mCamPos.x += CAM_SPEED * (GLfloat)mTimeDiff /1000;
		}
		if (g_Keystate['D'] == TRUE)
		{
			mCamPos.x -= CAM_SPEED * (GLfloat)mTimeDiff /1000;
		}
		*/

		mpCamera->setPosition(mPlayer->getPosition());
	};

	void processPlayerInput()
	{
		bool bMoving = false;

		if ((g_Keystate[VK_LEFT] != TRUE) || (g_Keystate[VK_RIGHT] != TRUE))
		{
			if (g_Keystate[VK_LEFT] == TRUE)
			{
				float angle = mPlayer->getRotation();
				mPlayer->setRotation(angle + (30 * (GLfloat)mTimeDiff /1000));

				if (gCollisionObjectList.checkCollision(mPlayer) == TRUE)
				{
					mPlayer->setRotation(angle);
				}

				/*mPlayer->setCurrentAnimation(ANIM_MOVE_LEFT);
				bMoving = true;*/
			}
			if (g_Keystate[VK_RIGHT] == TRUE)
			{
				float angle = mPlayer->getRotation();
				mPlayer->setRotation(angle - (30 * (GLfloat)mTimeDiff /1000));

				if (gCollisionObjectList.checkCollision(mPlayer) == TRUE)
				{
					mPlayer->setRotation(angle);
				}

				/*mPlayer->setCurrentAnimation(ANIM_MOVE_RIGHT);
				bMoving = true;*/
			}
		}

		if ((g_Keystate[VK_UP] != TRUE) || (g_Keystate[VK_DOWN] != TRUE))
		{
			if (g_Keystate[VK_UP] == TRUE)
			{
				CVector2f pos = mPlayer->getPosition();
				mPlayer->moveForward(CAM_SPEED * (GLfloat)mTimeDiff /1000);

				if (gCollisionObjectList.checkCollision(mPlayer) == TRUE)
				{
					mPlayer->setPosition(pos);
				}

				if (mPlayer->getCurrentAnimation() != ANIM_MOVE_LEFT)
				{
					mPlayer->setCurrentAnimation(ANIM_MOVE_RIGHT);
				}
				bMoving = true;
			}
			if (g_Keystate[VK_DOWN] == TRUE)
			{
				CVector2f pos = mPlayer->getPosition();
				mPlayer->moveForward(- CAM_SPEED * (GLfloat)mTimeDiff /1000);

				if (gCollisionObjectList.checkCollision(mPlayer) == TRUE)
				{
					mPlayer->setPosition(pos);
				}

				if (mPlayer->getCurrentAnimation() != ANIM_MOVE_RIGHT)
				{
					mPlayer->setCurrentAnimation(ANIM_MOVE_LEFT);
				}
				bMoving = true;
			}
		}

		if (bMoving == false)
		{
			mPlayer->setCurrentAnimation(ANIM_NONE);
		}
	};

	CPlayerSprite* mPlayer;
	CPlayerSprite* mPlayer2;
	CMap2D* mpMap;

	CCamera* mpCamera;

	bool dir;
};

#endif