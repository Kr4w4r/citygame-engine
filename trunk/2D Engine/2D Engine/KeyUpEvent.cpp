#include "KeyDownEvent.h"

CKeyUpEvent::CKeyUpEvent(CHAR key, BOOLEAN bAlt, ULONG timestamp)
:CEvent(timestamp)
{
	mEventType = EVENT_KEYBOARD_KEY_DOWN;

	mEventData.key = key;
	mEventData.bAlt = bAlt;
}

CKeyUpEvent::~CKeyUpEvent()
{
}

T_KEYBOARD_EVENT_DATA CKeyUpEvent::getEventData()
{
	return mEventData;
}