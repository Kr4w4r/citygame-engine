#include "KeyboardBindings.h"

CKeyboardBindings::CKeyboardBindings()
{}

CKeyboardBindings::~CKeyboardBindings()
{}

void CKeyboardBindings::setKeystate(CHAR key, BOOLEAN bPressed) 
{ 
	mKeystate[key] = bPressed; 
}