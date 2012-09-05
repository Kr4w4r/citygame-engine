#ifndef IEVENTLISTENER_H
#define IEVENTLISTENER_H

#include "IEvent.h"

class IEventListener
{
public:
	/**************************************************************************
	@brief		bearbeitet das übergebene Event

	@param[in] IEvent* event	Event das bearbeitet werden soll

	@return		-c true		Event verbraucht und sollte NICHT weiterverteilt werden
				-c false	Event normal verarbeitet
	**************************************************************************/
	virtual BOOLEAN handleEvent(IEvent* event) = 0;

};

#endif