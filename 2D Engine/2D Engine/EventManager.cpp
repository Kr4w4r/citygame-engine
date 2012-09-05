#include "EventManager.h"

/**************************************************************************
	Static Methoden
**************************************************************************/
IEventManager* CEventManager::getInstance()
{
	static CEventManager eventManager;
	return &eventManager;
}

/**************************************************************************
	normale Methoden
**************************************************************************/
CEventManager::CEventManager()
:mRegisteredEvents()
,mEventListenerMap()
{
	mpReadQueue = &mEventQueue[0];
	mpWriteQueue = &mEventQueue[1];
}

CEventManager::~CEventManager()
{
	// alles Aufräumen

}

void CEventManager::addEventListener(IEventListener* pEventListener, EVENT_TYPE triggerType)
{
	// zuerst den EventType in das Set der verarbeiteten Events aufnehmen
	mRegisteredEvents.insert(triggerType);
	
	// Liste der Eventlistener für diesen Eventtypen holen
	EventListenerMap::iterator mapIt = mEventListenerMap.find(triggerType);
	
	if (mapIt == mEventListenerMap.end())
	{
		mEventListenerMap.insert(pair<EVENT_TYPE, EventListenerList>(triggerType, EventListenerList()));

		mapIt = mEventListenerMap.find(triggerType);
	}

	EventListenerList& eventListenerList = (EventListenerList&)(*mapIt).second;

	// verhindern das wir einen Listener 2mal einfügen
	for (EventListenerList::iterator iter = eventListenerList.begin(); 
		iter != eventListenerList.end(); iter++)
	{
		if ((*iter) == pEventListener)
			return ;
	}
	// ok ist noch nicht vorhanden, also rein damit
	eventListenerList.push_back(pEventListener);
}

void CEventManager::deleteEventListener(IEventListener* pEventListener, EVENT_TYPE triggerType)
{
	// wir löschen den Eventlister für ein bestimmtes Event
	EventListenerMap::iterator mapIter = mEventListenerMap.find(triggerType);
	
	if (mapIter != mEventListenerMap.end())
	{
		EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
		
		for (EventListenerList::iterator iter = eventListenerList.begin(); 
			iter != eventListenerList.end(); iter++)
		{
			if ((*iter) == pEventListener)
			{
				eventListenerList.erase(iter);
				return;
			}
		}
	}
}

void CEventManager::deleteEventListener(IEventListener* pEventListener)
{
	// wir löschen den Eventlister komplett aus allen Listen
	for (EventListenerMap::iterator mapIter = mEventListenerMap.begin(); 
		mapIter != mEventListenerMap.end(); mapIter++)
	{
		EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
		
		for (EventListenerList::iterator iter = eventListenerList.begin(); 
			iter != eventListenerList.end(); iter++)
		{
			if ((*iter) == pEventListener)
			{
				eventListenerList.erase(iter);
			}
		}
	}
}

/**************************************************************************
@brief		Triggert alle Listener für das Event genau JETZT (synchrone Verarbeitung)

@param[in] IEvent* event	Event das ausgeführt werden soll

@return		-c TRUE		Event wurde verarbeitet
			-c FALSE	Event normal verarbeitet
**************************************************************************/
BOOLEAN CEventManager::triggerEvent(IEvent* pTriggerEvent)
{
	// wir löschen den Eventlister für ein bestimmtes Event
	EventListenerMap::iterator mapIter = mEventListenerMap.find(pTriggerEvent->getType());
	
	if (mapIter != mEventListenerMap.end())
	{
		EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
		
		// Jedem Eventlistener das Event übergeben, es sei denn der Listener 
		// sagt, dass die Verteilung gestoppt werden soll
		for (EventListenerList::iterator iter = eventListenerList.begin(); 
			iter != eventListenerList.end(); iter++)
		{
			if ((*iter)->handleEvent(pTriggerEvent) == TRUE)
			{
				return TRUE;
			}
		}
	}

	// alles ohne Probleme verlaufen
	return FALSE;
}

/**************************************************************************
@brief		Queue das übergebene Event ein, damit es bei trigger() ausgeführt wird

@param[in] IEvent* event	Event das eingefügt werden soll

@return		-c TRUE		Event wurde eingefügt
			-c FALSE	Fehler beim einfügen
**************************************************************************/
BOOLEAN CEventManager::queueEvent(IEvent* pEvent)
{
	// können wir das Event überhaupt verarbeiten?
	EventSet::iterator setIter = mRegisteredEvents.find(pEvent->getType());
	if (setIter == mRegisteredEvents.end())
	{
		// das Event wird von keinem Listener angenommen
		return FALSE;
	}

	// Event einfügen
	mpWriteQueue->push_back(pEvent);

	return TRUE;
}

/**************************************************************************
@brief		Entfernt das erste Event von dem angegebenen Typen aus der EventQueue
			oder alle wenn abortAll = TRUE

@param[in] EVENT_TYPE eventType		Typ des Events welches entfernt werden soll
@param[in] BOOLEAN abortAll			gibt an ob nur das erste oder alle Events 
									des Typen aus der Queue entfernt werden soll

@return		-c TRUE		Event(s) erfolgreich gelöscht
			-c FALSE	Fehler beim löschen (keins mehr vorhanden?)
**************************************************************************/
BOOLEAN CEventManager::abortEvent(EVENT_TYPE eventType, BOOLEAN bAbortAll)
{
	BOOLEAN bEventAborted = FALSE;

	for (EventQueue::iterator iter = mpWriteQueue->begin(); iter != mpWriteQueue->end(); iter++)
	{
		if ((*iter)->getType() == eventType)
		{
			EventQueue::iterator eraseIter = iter;

			iter--;
			mpWriteQueue->erase(eraseIter);

			if (bAbortAll == FALSE)
			{
				return TRUE;
			}

			bEventAborted = TRUE;
		}
	}

	return bEventAborted;
}

/**************************************************************************
@brief		Führt alle Events in der Event-Queue aus, bis das Zeitlimit 
			erreicht wurde

@param[in] ULONG timeLimit		Zeitlimit zur Bearbeitung in millisek.; Nach 
								Ablauf der Zeit werden die übrigen Events verworfen

@return		-c TRUE		Alle Events verabeitet
			-c FALSE	Nicht alle Events verarbeitet (Timeout)
**************************************************************************/
BOOLEAN CEventManager::tick(ULONG timeLimit)
{
	// Endzeit bestimmen, da infinite ein riesiger Wert ist (0xFFFFFFFF) und es fast 50 Tage 
	// braucht bis wir die Grenze erreichen, brauchen wir hier keine spezialbehandlung
	ULONG maxTime = GetTickCount() + timeLimit;

	// EventQueue tauschen
	EventQueue* tempQueue = mpReadQueue;
	mpReadQueue = mpWriteQueue;
	mpWriteQueue = tempQueue;
	// und die Queue für neue Events frei machen
	mpWriteQueue->clear();

	BOOLEAN bTimeoutOver = FALSE;
	// Alle Events durchgehen
	while ((mpReadQueue->size() > 0) && (bTimeoutOver == FALSE))
	{
		IEvent* pEvent = mpReadQueue->front();
		mpReadQueue->pop_front();

		// Zu dem Event alle zugehörigen Listener suchen
		EventListenerMap::iterator mapIter = mEventListenerMap.find(pEvent->getType());
		if (mapIter != mEventListenerMap.end())
		{
			EventListenerList& eventListenerList = (EventListenerList&)(*mapIter);
			// und zum Schluss noch das Event von allen Listener verarbeiten lassen
			for (EventListenerList::iterator listenerIter = eventListenerList.begin(); 
				listenerIter != eventListenerList.end(); listenerIter++)
			{
				// wenn die Verarbeitung des Events abgebrochen werden soll, hören 
				// wir auf das Event an die weiteren Listener weiterzugeben
				if ((*listenerIter)->handleEvent(pEvent) == TRUE)
					break;
			}
		}
		// natürlich müssen wir noch prüfen ob wir noch im Zeitlimit liegen
		// dann brechen wir die Verarbeitung ab
		if (GetTickCount() >= maxTime)
			bTimeoutOver = TRUE;
	}

	BOOLEAN bQueueEmpty = TRUE;

	// wenn nicht alle Events verarbeitet werden konnten, können diese natürlich 
	// nicht verloren gehen also in die WriteQueue schieben. 
	while (mpReadQueue->size() > 0)
	{
		bQueueEmpty = FALSE;

		// dazu das Ende der ReadQueue an den Anfang der WriteQueue verschieben
		IEvent* pEvent = mpReadQueue->back();
		mpReadQueue->pop_back();
		mpWriteQueue->push_front(pEvent);
	}

	return bQueueEmpty;
}

/**************************************************************************
@brief		Prüft ob der Angegebene EventType von irgendeinem Listener 
			überhaupt empfangen und damit auch verarbeitet wird

@param[in] EVENT_TYPE eventType		EventType der geprüft werden soll

@return		-c TRUE		Event wird verarbeitet
			-c FALSE	Event kann nicht verbeitet werden
**************************************************************************/
BOOLEAN CEventManager::validateType(EVENT_TYPE eventType)
{
	return TRUE;
}