#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

#include "Event.h"
#include "KeyUpEvent.h"

class CKeyDownEvent : public CEvent
{
public:
	CKeyDownEvent(CHAR key, BOOLEAN bAlt, ULONG timestamp);
	virtual ~CKeyDownEvent();

	T_KEYBOARD_EVENT_DATA getEventData();
protected:
	T_KEYBOARD_EVENT_DATA mEventData;
};

#endif