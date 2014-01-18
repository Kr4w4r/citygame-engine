#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

const int MAX_KEYSTATES = 256;

class CKeyboardAction
{
	CKeyboardAction();
	virtual ~CKeyboardAction();


};

class CKeyboardBindings
{
public:
	CKeyboardBindings();
	virtual ~CKeyboardBindings();

	void setKeystate(CHAR key, BOOLEAN bPressed);

	virtual void checkBindings(ULONG deltaMilliseconds) = 0;
	
protected:
	
	BOOLEAN mKeystate[MAX_KEYSTATES];
};