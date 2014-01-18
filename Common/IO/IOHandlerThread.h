#pragma once

#include "Thread.h"
#include "EventListener.h"
#include "KeyboardBindings.h"

class CIOHandlerThread : CEventListener
{
public:
	CIOHandlerThread(CKeyboardBindings* pKeyboardBindings);
	virtual ~CIOHandlerThread();

	/**************************************************************************
	@brief		bearbeitet das übergebene Event

	@param[in] IEvent* event	Event das bearbeitet werden soll

	@return		-c true		Event verbraucht und sollte NICHT weiterverteilt werden
				-c false	Event normal verarbeitet
	**************************************************************************/
	virtual BOOLEAN handleEvent(IEvent* event);

protected:
	CKeyboardBindings* mpKeyboardBindings;
};