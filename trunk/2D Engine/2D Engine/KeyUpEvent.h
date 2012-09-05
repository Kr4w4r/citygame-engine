#ifndef KEY_UP_EVENT_H
#define KEY_UP_EVENT_H

#include "Event.h"

typedef struct KEYBOARD_EVENT_DATA
{
	CHAR key;
	BOOLEAN bShift;
	BOOLEAN bCrtl;
	BOOLEAN bAlt;
} T_KEYBOARD_EVENT_DATA;

class CKeyUpEvent : public CEvent
{
public:
	CKeyUpEvent(CHAR key, BOOLEAN bAlt, ULONG timestamp);
	virtual ~CKeyUpEvent();

	T_KEYBOARD_EVENT_DATA getEventData();
protected:
	T_KEYBOARD_EVENT_DATA mEventData;
};

#endif