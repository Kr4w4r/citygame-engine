#include "KeyboardEvent.h"

const CEventType CKeyboardEvent::msEventType("KeyboardEvent");

CKeyboardEvent::CKeyboardEvent(CHAR key, BOOLEAN bDown)
	:mKeyPressed(key)
	,mbDown(bDown)
{
}

CKeyboardEvent::~CKeyboardEvent()
{}

const CEventType& CKeyboardEvent::getType() const
{
	return msEventType;
}