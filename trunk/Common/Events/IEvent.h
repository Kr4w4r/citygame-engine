#ifndef IEVENT_H
#define IEVENT_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "EventList.h"

class IEvent
{
public:
	virtual EVENT_TYPE getType() = 0;
	virtual ULONG getTimestamp() = 0;
};

#endif