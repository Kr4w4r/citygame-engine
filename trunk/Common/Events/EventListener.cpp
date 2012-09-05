#include "EventListener.h"

CEventListener::CEventListener()
{
}

CEventListener::~CEventListener()
{
}

/**************************************************************************
@brief		bearbeitet das übergebene Event

@param[in] IEvent* event	Event das bearbeitet werden soll

@return		-c true		Event verbraucht und sollte NICHT weiterverteilt werden
			-c false	Event normal verarbeitet
**************************************************************************/
BOOLEAN CEventListener::handleEvent(IEvent *event)
{
	// im standardlistener machen wir nichts und das Event soll weiterverteilt werden
	return false;
}