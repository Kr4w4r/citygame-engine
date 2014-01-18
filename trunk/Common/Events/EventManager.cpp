#include "EventManager.h"

#include <string>
using std::string;

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
:CThread(EVENT_MANAGER_THREAD_NAME, 0, TRUE)
,mRegisteredEvents()
,mEventListenerMap()
,mWriteQueueCS("writeQueueCS")
,mListenerCS("ListenerCS")
{
	OutputDebugString("constructed");
	mpReadQueue = &mEventQueue[0];
	mpWriteQueue = &mEventQueue[1];

	trigger();
}

CEventManager::~CEventManager()
{
	// alles Aufräumen
	prepareDelete();
	while (isReadyForDelete() == false)
	{}
}

void CEventManager::threadMethod()
{
	tick(INFINITE);
}

void CEventManager::addEventListener(IEventListener* pEventListener, CEventType triggerType)
{
	CCriticalBlock cs(&mListenerCS);

	// zuerst den EventType in das Set der verarbeiteten Events aufnehmen
	mRegisteredEvents.insert(triggerType);
	
	// Liste der Eventlistener für diesen Eventtypen holen
	EventListenerMapIter mapIt = mEventListenerMap.find(triggerType);
	if (mapIt == mEventListenerMap.end())
	{
		mEventListenerMap.insert(pair<CEventType, EventListenerList>(triggerType, EventListenerList()));

		mapIt = mEventListenerMap.find(triggerType);
	}

	EventListenerList& eventListenerList = (EventListenerList&)(*mapIt).second;

	// verhindern das wir einen Listener 2mal einfügen
	for (EventListenerListIter iter = eventListenerList.begin(); 
		iter != eventListenerList.end(); iter++)
	{
		if ((*iter) == pEventListener)
		{
			mListenerCS.leave();
			return ;
		}
	}
	// ok ist noch nicht vorhanden, also rein damit
	eventListenerList.push_back(pEventListener);
}

void CEventManager::deleteEventListener(IEventListener* pEventListener, CEventType triggerType)
{
	CCriticalBlock cs(&mListenerCS);

	// wir löschen den Eventlister für ein bestimmtes Event
	EventListenerMapIter mapIter = mEventListenerMap.find(triggerType);
	if (mapIter != mEventListenerMap.end())
	{
		EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
		
		for (EventListenerListIter iter = eventListenerList.begin(); 
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
	CCriticalBlock cs(&mListenerCS);

	// wir löschen den Eventlister komplett aus allen Listen
	for (EventListenerMapIter mapIter = mEventListenerMap.begin(); 
		mapIter != mEventListenerMap.end(); mapIter++)
	{
		EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
		
		for (EventListenerListIter iter = eventListenerList.begin(); 
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
	BOOLEAN bRet = FALSE;

	CCriticalBlock cs(&mListenerCS);

	// wir suchen den Eventlister für ein bestimmtes Event
	EventListenerMapIter mapIter = mEventListenerMap.find(pTriggerEvent->getType());
	if (mapIter != mEventListenerMap.end())
	{
		EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
		
		// Jedem Eventlistener das Event übergeben, es sei denn der Listener 
		// sagt, dass die Verteilung gestoppt werden soll
		for (EventListenerListIter iter = eventListenerList.begin(); 
			iter != eventListenerList.end(); iter++)
		{
			if ((*iter)->handleEvent(pTriggerEvent) == TRUE)
			{
				return TRUE;
			}
		}
	}

	// alles ohne Probleme verlaufen und das Event wurde nicht Konsumiert
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
	EventSetIter setIter = mRegisteredEvents.find(pEvent->getType());
	if (setIter == mRegisteredEvents.end())
	{
		string output = "CEventManager::queueEvent => No listener registered that would handle the '" + pEvent->getType().getName() + "'-Event.\n";
		OutputDebugString(output.c_str());

		// das Event wird von keinem Listener angenommen
		return FALSE;
	}

	mWriteQueueCS.enter();
	{
		// Event einfügen
		mpWriteQueue->push_back(pEvent);
	}
	mWriteQueueCS.leave();
	return TRUE;
}

/**************************************************************************
@brief		Entfernt das erste Event von dem angegebenen Typen aus der EventQueue
			oder alle wenn abortAll = TRUE

@param[in] CEventType eventType		Typ des Events welches entfernt werden soll
@param[in] BOOLEAN abortAll			gibt an ob nur das erste oder alle Events 
									des Typen aus der Queue entfernt werden soll

@return		-c TRUE		Event(s) erfolgreich gelöscht
			-c FALSE	Fehler beim löschen (keins mehr vorhanden?)
**************************************************************************/
BOOLEAN CEventManager::abortEvent(CEventType eventType, BOOLEAN bAbortAll)
{
	CCriticalBlock cs(&mWriteQueueCS);

	BOOLEAN bEventAborted = FALSE;

	for (EventQueueIter iter= mpWriteQueue->begin(); iter != mpWriteQueue->end(); iter++)
	{
		if ((*iter)->getType() == eventType)
		{
			EventQueueIter eraseIter = iter;

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

	mWriteQueueCS.enter();
	{
		// EventQueue tauschen
		EventQueue* tempQueue = mpReadQueue;
		mpReadQueue = mpWriteQueue;
		mpWriteQueue = tempQueue;

		if (mpWriteQueue->size() > 0)
		{
			// und die Queue für neue Events frei machen
			mpWriteQueue->clear();
		}
	}
	mWriteQueueCS.leave();

	BOOLEAN bTimeoutOver = FALSE;
	// Alle Events durchgehen
	while ((mpReadQueue->size() > 0) && (bTimeoutOver == FALSE))
	{
		IEvent* pEvent = mpReadQueue->front();
		mpReadQueue->pop_front();

		mListenerCS.enter();

		// Zu dem Event alle zugehörigen Listener suchen
		EventListenerMapIter mapIter = mEventListenerMap.find(pEvent->getType());
		if (mapIter != mEventListenerMap.end())
		{
			EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
			// und zum Schluss noch das Event von allen Listener verarbeiten lassen
			for (EventListenerListIter listenerIter = eventListenerList.begin(); 
				listenerIter != eventListenerList.end(); listenerIter++)
			{
				// wenn die Verarbeitung des Events abgebrochen werden soll, hören 
				// wir auf das Event an die weiteren Listener weiterzugeben
				if ((*listenerIter)->handleEvent(pEvent) == TRUE)
					break;
			}
		}

		mListenerCS.leave();

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

		mWriteQueueCS.enter();
		{
			// dazu das Ende der ReadQueue an den Anfang der WriteQueue verschieben
			IEvent* pEvent = mpReadQueue->back();
			mpReadQueue->pop_back();
			mpWriteQueue->push_front(pEvent);
		}
		mWriteQueueCS.leave();
	}

	return bQueueEmpty;
}

/**************************************************************************
@brief		Prüft ob der Angegebene EventType von irgendeinem Listener 
			überhaupt empfangen und damit auch verarbeitet wird

@param[in] CEventType eventType		EventType der geprüft werden soll

@return		-c TRUE		Event wird verarbeitet
			-c FALSE	Event kann nicht verbeitet werden
**************************************************************************/
BOOLEAN CEventManager::validateType(CEventType eventType)
{
	return TRUE;
}