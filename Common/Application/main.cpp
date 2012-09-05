#include <windows.h>

#include "TestApp.h"
//#include "EventManager.h"
//#include "KeyboardEvent.h"

#include "boost/config.hpp"
#include "boost/shared_ptr.hpp"
using boost::shared_ptr;

HDC		hDC = NULL;
HGLRC	hRC = NULL;
HWND	hWnd = NULL;
HINSTANCE hInstance;

// sollte eigentlich duch den Controlmanager nicht mehr benötigt werden
// da aber einige ältere Programme dieses Array noch brauchen bleibt es hier stehen
#pragma message ("[main.cpp] Keystate Array entfernen und alle Apps auf CControlManager ändern")
BOOLEAN g_Keystate[256];
// wir haben hier die Position relativ zur Oberen Linken Ecke des Fensters
INT g_MouseX;
INT g_MouseY;

CTestApp g_application(hDC, hWnd);

CHAR gExeFilePath[MAX_PATH];

//extern CEventManager g_EventManager;

LRESULT CALLBACK WndProc(	HWND	hWnd,
							UINT	uMsg,
							WPARAM	wParam,
							LPARAM	lParam)
{
	switch(uMsg)
	{
		case WM_CLOSE:
		case WM_QUIT:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_SIZE:
		{
			INT width = LOWORD(lParam);
			INT height = HIWORD(lParam);
			g_application.establishProjectionMatrix(width, height);
			break;
		}
		case WM_KEYDOWN:
		{
			//CEventManager::getInstance()->queueEvent(new 
			g_Keystate[wParam] = TRUE;

			//shared_ptr<CKeyboardEvent> keyboardEvent(new CKeyboardEvent(wParam, true));
			//g_EventManager.VQueueEvent(keyboardEvent);
			break;
		}
		case WM_KEYUP:
		{
			g_Keystate[wParam] = FALSE;
			//shared_ptr<CKeyboardEvent> keyboardEvent(new CKeyboardEvent(wParam, false));
			//g_EventManager.VQueueEvent(keyboardEvent);
			break;
		}
		case WM_SYSKEYDOWN:
		{
			OutputDebugString("syskeyDown\n");
			break;
		}
		case WM_SYSKEYUP:
		{
			OutputDebugString("syskeyUp\n");
			break;
		}
		case WM_LBUTTONDOWN:
			{
	            g_MouseX = LOWORD(lParam);          
				g_MouseY = HIWORD(lParam);
				
				// Event senden
				//Selection();
			}
		break;

		case WM_MOUSEMOVE:
			{
				// wir haben hier die Position relativ zur Oberen Linken Ecke des Fensters
	            g_MouseX = LOWORD(lParam);          
				g_MouseY = HIWORD(lParam);
/*
				CHAR output[256];
				sprintf(output, "Mousemove x: %u, y: %u\n", g_MouseX, g_MouseY);
				OutputDebugString(output);
*/
			}
		break;
		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOLEAN createGLWindow( char* title, int width, int height, int bits)
{
	GLuint	pixelFormat;

	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;

	RECT		windowRect;

	windowRect.left = 10;
	windowRect.right = width;
	windowRect.top = 10;
	windowRect.bottom = height;

	hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenGL";

	RegisterClass(&wc);

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPEDWINDOW;

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	hWnd = CreateWindowEx(	dwExStyle,
							"OpenGL",
							title,
							dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
							0,0,
							width,height,
							NULL, 
							NULL,
							hInstance,
							NULL);

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1, 
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	hDC = GetDC(hWnd);
	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);

	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	return TRUE;
}

BOOLEAN killWindow()
{
	if (hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);
		hRC = NULL;
	}

	if (!(hDC && ReleaseDC(hWnd, hDC)))
	{
		// Fehlermeldung schicken
		return FALSE;
	}

	if (!(hWnd && DestroyWindow(hWnd)))
	{
		// Fehlermeldung schicken
		return FALSE;
	}

	UnregisterClass("OpenGL", hInstance);

	return TRUE;
}

int WINAPI WinMain(	HINSTANCE	hInstance, 
					HINSTANCE	hPrevInstance, 
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	GetModuleFileName(NULL, gExeFilePath, MAX_PATH);
	(*strrchr(gExeFilePath, '\\')) = '\0';

	MSG msg;
	INT done = 0;

	if (createGLWindow("Ant Me!", windowWidth, windowHeight, windowBits) == FALSE)
	{
		killWindow();

		return 0;
	}

	g_application.initGL(windowWidth, windowHeight);

	while (done != TRUE)
	{
		// nun betreten wir unser Programm
		done = (INT)!g_application.enter();

		// anzeigen
		glFlush();
		SwapBuffers(hDC);

		while (PeekMessage(&msg, NULL, 0,0, PM_REMOVE) == TRUE)
		{
			if ((msg.message == WM_QUIT) || (msg.message == WM_DESTROY) || (msg.message == WM_CLOSE))
			{
				done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	killWindow();

	return (INT)(msg.wParam);
}
