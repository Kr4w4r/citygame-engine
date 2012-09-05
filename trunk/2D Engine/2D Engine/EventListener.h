#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "IEventListener.h"

class CEventListener : public IEventListener
{
public:
	CEventListener();
	~CEventListener();

	/**************************************************************************
	@brief		bearbeitet das übergebene Event

	@param[in] IEvent* event	Event das bearbeitet werden soll

	@return		-c true		Event verbraucht und sollte NICHT weiterverteilt werden
				-c false	Event normal verarbeitet
	**************************************************************************/
	virtual BOOLEAN handleEvent(IEvent* event);

};

#endif