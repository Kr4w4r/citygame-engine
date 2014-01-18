#pragma once

#include "Event.h"

class CTickEvent : public CEvent
{
public:
	CTickEvent(ULONG deltaMilliseconds);
	virtual ~CTickEvent();

	virtual const CEventType& getType() const;

	ULONG getDeltaMilliseconds() { return mDeltaMilliseconds; };

public:
	static const CEventType msEventType;

protected:
	ULONG mDeltaMilliseconds;
};