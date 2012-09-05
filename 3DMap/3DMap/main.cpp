// 3DMap.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "stdafx.h"
#include "main.h"

#include "MapApplication.h"


#define MAX_LOADSTRING 100

BOOLEAN g_Keystate[256];

// Globale Variablen:
HDC		hDC = NULL;
HGLRC	hRC = NULL;
HWND	hWnd = NULL;
HINSTANCE hInstance;							// Aktuelle Instanz
TCHAR szTitle[MAX_LOADSTRING];					// Titelleistentext
TCHAR szWindowClass[MAX_LOADSTRING];			// Klassenname des Hauptfensters

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOLEAN createGLWindow(int width, int height, int bits);
BOOLEAN killWindow();


CMapApplication g_application(hDC, hWnd);

int APIENTRY _tWinMain(HINSTANCE hInst,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Hier Code einfügen.
	MSG msg;
	HACCEL hAccelTable;

	// Globale Zeichenfolgen initialisieren
	LoadString(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInst, IDC_MY3DMAP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInst);

	// Anwendungsinitialisierung ausführen:
	if (!InitInstance (hInst, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_MY3DMAP));

	g_application.initGL(windowWidth, windowHeight);

	BOOLEAN done = FALSE;
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



//
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
//
//  KOMMENTARE:
//
//    Sie müssen die Funktion verwenden,  wenn Sie möchten, dass der Code
//    mit Win32-Systemen kompatibel ist, bevor die RegisterClassEx-Funktion
//    zu Windows 95 hinzugefügt wurde. Der Aufruf der Funktion ist wichtig,
//    damit die kleinen Symbole, die mit der Anwendung verknüpft sind,
//    richtig formatiert werden.
//
ATOM MyRegisterClass(HINSTANCE hInst)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_MY3DMAP));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;MAKEINTRESOURCE(IDC_MY3DMAP);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNKTION: InitInstance(HINSTANCE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTARE:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{

	hInstance = hInst; // Instanzenhandle in der globalen Variablen speichern
	/*
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);
	*/

   createGLWindow(800, 600, 32);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
//  WM_COMMAND	- Verarbeiten des Anwendungsmenüs
//  WM_PAINT	- Zeichnen des Hauptfensters
//  WM_DESTROY	- Beenden-Meldung anzeigen und zurückgeben
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Menüauswahl bearbeiten:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Hier den Zeichnungscode hinzufügen.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
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
	case WM_SIZE:
		{
			INT width = LOWORD(lParam);
			INT height = HIWORD(lParam);
			g_application.establishProjectionMatrix(width, height);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Meldungshandler für Infofeld.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/

BOOLEAN createGLWindow(int width, int height, int bits)
{
	if ((width == 0) || (height))
	{
		width = CW_USEDEFAULT;
		height = 0;
	}

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
							"Title",
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