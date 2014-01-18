#include "IOHandlerThread.h"

#include "EventManager.h"
#include "KeyboardEvent.h"
#include "TickEvent.h"

#include <string>
using std::string;

CIOHandlerThread::CIOHandlerThread(CKeyboardBindings* pKeyboardBindings)
:CEventListener()
{
	mpKeyboardBindings = pKeyboardBindings;

	CEventManager::getInstance()->addEventListener(this, CKeyboardEvent::msEventType);
}

CIOHandlerThread::~CIOHandlerThread()
{
}

/**************************************************************************
@brief		bearbeitet das übergebene Event

@param[in] IEvent* event	Event das bearbeitet werden soll

@return		-c true		Event verbraucht und sollte NICHT weiterverteilt werden
			-c false	Event normal verarbeitet
**************************************************************************/
BOOLEAN CIOHandlerThread::handleEvent(IEvent* event)
{
	if (event->getType() == CKeyboardEvent::msEventType)
	{
		CKeyboardEvent* pKeyEvent = (CKeyboardEvent*)event;
		
		string out = "Key '" ;//+ pKeyEvent->getKeyPressed();
		out.push_back(pKeyEvent->getKeyPressed());
		out += "' is ";
		out += (pKeyEvent->isKeyDown() ? "pressed.\n" : "released.\n");

		OutputDebugString(out.c_str());

		mpKeyboardBindings->setKeystate(pKeyEvent->getKeyPressed(), pKeyEvent->isKeyDown());
	}
	else if (event->getType() == CTickEvent::msEventType)
	{
		CTickEvent* pTickEvent = (CTickEvent*)event;

		mpKeyboardBindings->checkBindings(pTickEvent->getDeltaMilliseconds());
	}

	return FALSE;
}