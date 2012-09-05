#ifndef MOUSECLICKEVENT_H
#define MOUSECLICKEVENT_H

#include "Event.h"

typedef struct MOUSE_CLICK_EVENT_DATA
{
	BOOLEAN leftClick;
	USHORT x;
	USHORT y;
} T_MOUSE_CLICK_EVENT_DATA;

class CMouseClickEvent : public CEvent
{
public:
	CMouseClickEvent(BOOLEAN leftClick, USHORT x, USHORT y, ULONG timestamp);
	virtual ~CMouseClickEvent();

	T_MOUSE_CLICK_EVENT_DATA getEventData();
protected:
	T_MOUSE_CLICK_EVENT_DATA mEventData;
};

#endif