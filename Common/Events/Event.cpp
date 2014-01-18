#include "Event.h"

CEvent::CEvent(ULONG timestamp) : IEvent()
{
	mTimestamp = timestamp;
}

CEvent::~CEvent()
{
}

ULONG CEvent::getTimestamp()
{
	return mTimestamp;
}