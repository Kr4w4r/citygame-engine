#ifndef EVENT_H
#define EVENT_H

#include "IEvent.h"

class CEvent : public IEvent
{
public:
	CEvent(ULONG timeStamp = 0);
	virtual ~CEvent();

	virtual ULONG getTimestamp();
	virtual EVENT_TYPE getType();

protected:
	EVENT_TYPE mEventType;
	ULONG mTimestamp;
};

#endif