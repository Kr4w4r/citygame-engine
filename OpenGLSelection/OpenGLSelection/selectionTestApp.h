#ifndef TEST_APP_H
#define TEST_APP_H

#include "2dApplication.h"

const GLfloat CAM_SPEED = 1.2f;

const GLint RED_QUAD = 1;
const GLint GREEN_QUAD = 2;
const GLint BLUE_QUAD = 3;
const GLint YELLOW_QUAD = 4;

class CSelectionTestApp : public C2DApplication
{
public:
	CSelectionTestApp(HDC &hDC, HWND &hWnd) : C2DApplication(hDC, hWnd) {};
	~CSelectionTestApp() 
	{
	};

protected:
	GLvoid test()
	{
	}

	virtual GLvoid initScene()
	{
	};

	virtual GLvoid drawScene() 
	{
		// Bildbuffer leeren
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Namestack reseten
		glRenderMode (GL_SELECT);
		glInitNames();
		glPushName(0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		// ModelviewMatrix auf dem Stack sichern
		glPushMatrix();
			glLoadName(RED_QUAD);
			glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(-1.0f,  1.0f, -3);
				glVertex3f( 0.2f,  1.0f, -3);
				glVertex3f( 0.2f, -0.2f, -3);
				glVertex3f(-1.0f, -0.2f, -3);
			glEnd();

			glLoadName(GREEN_QUAD);
			glBegin(GL_QUADS);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f( 1.0f,  1.0f, -3.5f);
				glVertex3f(-0.2f,  1.0f, -3.5f);
				glVertex3f(-0.2f, -0.1f, -3.5f);
				glVertex3f( 1.0f, -0.1f, -3.5f);
			glEnd();

			glLoadName(BLUE_QUAD);
			glBegin(GL_QUADS);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f( 1.0f, -1.0f, -4);
				glVertex3f(-0.2f, -1.0f, -3);
				glVertex3f(-0.2f,  0.2f, -3);
				glVertex3f( 1.0f,  0.2f, -3);
			glEnd();

			glLoadName(YELLOW_QUAD);
			glBegin(GL_QUADS);
				glColor3f(1.0f, 1.0f, 0.0f);
				glVertex3f(-1.0f, -1.0f, -5);
				glVertex3f( 0.2f, -1.0f, -5);
				glVertex3f( 0.2f,  0.2f, -5);
				glVertex3f(-1.0f,  0.2f, -5);
			glEnd();
		glPopMatrix();

	};

	virtual GLvoid updateScene() 
	{
		//processPlayerInput();
		//processCameraInput();
	};

	void processCameraInput()
	{
	};

	void processPlayerInput()
	{
	};

	void selection()
	{
		GLuint selectBuf[BUFSIZE];
		GLint hits;

		glSelectBuffer (BUFSIZE, selectBuf);
		(void) glRenderMode (GL_SELECT);

		

	};
};

#endif