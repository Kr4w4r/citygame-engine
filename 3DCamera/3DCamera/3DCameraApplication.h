#pragma once

#include "3DApplication.h"
#include "3DCamera.h"

class C3DCameraApplication : public C3DApplication
{
public:
	C3DCameraApplication(HDC &hDC, HWND &hWnd);
	virtual ~C3DCameraApplication(void);

protected:
	virtual GLvoid initScene();
	virtual GLvoid updateScene();	
	virtual GLvoid drawScene();

protected:
	C3DCamera* mpCamera;
};

