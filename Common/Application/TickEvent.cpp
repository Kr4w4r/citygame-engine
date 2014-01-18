#include "TickEvent.h"

const CEventType CTickEvent::msEventType("TickEvent");

CTickEvent::CTickEvent(ULONG deltaMilliseconds)
	:mDeltaMilliseconds(deltaMilliseconds)
{
}

CTickEvent::~CTickEvent()
{}

const CEventType& CTickEvent::getType() const
{
	return msEventType;
}