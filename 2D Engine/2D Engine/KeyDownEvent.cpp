#include "KeyDownEvent.h"

CKeyDownEvent::CKeyDownEvent(CHAR key, BOOLEAN bAlt, ULONG timestamp)
:CEvent(timestamp)
{
	mEventType = EVENT_KEYBOARD_KEY_DOWN;

	mEventData.key = key;
	mEventData.bAlt = bAlt;
}

CKeyDownEvent::~CKeyDownEvent()
{
}

T_KEYBOARD_EVENT_DATA CKeyDownEvent::getEventData()
{
	return mEventData;
}