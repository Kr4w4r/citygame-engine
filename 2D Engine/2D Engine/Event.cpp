#include "Event.h"

CEvent::CEvent(ULONG timestamp)
{
	mTimestamp = timestamp;
}

CEvent::~CEvent()
{
}

EVENT_TYPE CEvent::getType()
{
	return mEventType;
}

ULONG CEvent::getTimestamp()
{
	return mTimestamp;
}