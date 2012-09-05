#include "MouseClickEvent.h"

CMouseClickEvent::CMouseClickEvent(BOOLEAN leftClick, USHORT x, USHORT y, ULONG timestamp)
:CEvent(timestamp)
{
	mEventType = EVENT_MOUSE_CLICK;

	mEventData.leftClick = leftClick;
	mEventData.x = x;
	mEventData.y = y;
}

CMouseClickEvent::~CMouseClickEvent()
{
}

T_MOUSE_CLICK_EVENT_DATA CMouseClickEvent::getEventData()
{
	return mEventData;
}