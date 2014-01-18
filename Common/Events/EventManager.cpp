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
	// alles Aufr�umen
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
	
	// Liste der Eventlistener f�r diesen Eventtypen holen
	EventListenerMapIter mapIt = mEventListenerMap.find(triggerType);
	if (mapIt == mEventListenerMap.end())
	{
		mEventListenerMap.insert(pair<CEventType, EventListenerList>(triggerType, EventListenerList()));

		mapIt = mEventListenerMap.find(triggerType);
	}

	EventListenerList& eventListenerList = (EventListenerList&)(*mapIt).second;

	// verhindern das wir einen Listener 2mal einf�gen
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

	// wir l�schen den Eventlister f�r ein bestimmtes Event
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

	// wir l�schen den Eventlister komplett aus allen Listen
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
@brief		Triggert alle Listener f�r das Event genau JETZT (synchrone Verarbeitung)

@param[in] IEvent* event	Event das ausgef�hrt werden soll

@return		-c TRUE		Event wurde verarbeitet
			-c FALSE	Event normal verarbeitet
**************************************************************************/
BOOLEAN CEventManager::triggerEvent(IEvent* pTriggerEvent)
{
	BOOLEAN bRet = FALSE;

	CCriticalBlock cs(&mListenerCS);

	// wir suchen den Eventlister f�r ein bestimmtes Event
	EventListenerMapIter mapIter = mEventListenerMap.find(pTriggerEvent->getType());
	if (mapIter != mEventListenerMap.end())
	{
		EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
		
		// Jedem Eventlistener das Event �bergeben, es sei denn der Listener 
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
@brief		Queue das �bergebene Event ein, damit es bei trigger() ausgef�hrt wird

@param[in] IEvent* event	Event das eingef�gt werden soll

@return		-c TRUE		Event wurde eingef�gt
			-c FALSE	Fehler beim einf�gen
**************************************************************************/
BOOLEAN CEventManager::queueEvent(IEvent* pEvent)
{
	// k�nnen wir das Event �berhaupt verarbeiten?
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
		// Event einf�gen
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

@return		-c TRUE		Event(s) erfolgreich gel�scht
			-c FALSE	Fehler beim l�schen (keins mehr vorhanden?)
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
@brief		F�hrt alle Events in der Event-Queue aus, bis das Zeitlimit 
			erreicht wurde

@param[in] ULONG timeLimit		Zeitlimit zur Bearbeitung in millisek.; Nach 
								Ablauf der Zeit werden die �brigen Events verworfen

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
			// und die Queue f�r neue Events frei machen
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

		// Zu dem Event alle zugeh�rigen Listener suchen
		EventListenerMapIter mapIter = mEventListenerMap.find(pEvent->getType());
		if (mapIter != mEventListenerMap.end())
		{
			EventListenerList& eventListenerList = (EventListenerList&)(*mapIter).second;
			// und zum Schluss noch das Event von allen Listener verarbeiten lassen
			for (EventListenerListIter listenerIter = eventListenerList.begin(); 
				listenerIter != eventListenerList.end(); listenerIter++)
			{
				// wenn die Verarbeitung des Events abgebrochen werden soll, h�ren 
				// wir auf das Event an die weiteren Listener weiterzugeben
				if ((*listenerIter)->handleEvent(pEvent) == TRUE)
					break;
			}
		}

		mListenerCS.leave();

		// nat�rlich m�ssen wir noch pr�fen ob wir noch im Zeitlimit liegen
		// dann brechen wir die Verarbeitung ab
		if (GetTickCount() >= maxTime)
			bTimeoutOver = TRUE;
	}

	BOOLEAN bQueueEmpty = TRUE;

	// wenn nicht alle Events verarbeitet werden konnten, k�nnen diese nat�rlich 
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
@brief		Pr�ft ob der Angegebene EventType von irgendeinem Listener 
			�berhaupt empfangen und damit auch verarbeitet wird

@param[in] CEventType eventType		EventType der gepr�ft werden soll

@return		-c TRUE		Event wird verarbeitet
			-c FALSE	Event kann nicht verbeitet werden
**************************************************************************/
BOOLEAN CEventManager::validateType(CEventType eventType)
{
	return TRUE;
}