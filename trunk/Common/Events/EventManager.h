#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "IEventManager.h"
#include "Thread.h"

#include <set>
#include <vector>
#include <list>
#include <map>
using namespace std;

const UCHAR NUM_EVENT_QUEUES = 2;
const CHAR EVENT_MANAGER_THREAD_NAME[] = "EventManagerThread";

class CEventManager : public IEventManager, public CThread
{
protected:
	// protected Konstruktor da singleton Klasse
	CEventManager();
public:
	~CEventManager();

	// Zugriff auf Singleton
	static IEventManager* getInstance();

	// Threadmethode zum verarbeiten der Events
	virtual void threadMethod();

	// Methoden f�r Eventlistener
	virtual void addEventListener(IEventListener* pEventListener, CEventType triggerType);
	virtual void deleteEventListener(IEventListener* pEventListener, CEventType triggerType);
	virtual void deleteEventListener(IEventListener* pEventListener);

	// Methoden f�r Events

	/**************************************************************************
	@brief		Triggert alle Listener f�r das Event genau JETZT

	@param[in] IEvent* event	Event das ausgef�hrt werden soll

	@return		-c true		Event verbraucht und sollte NICHT weiterverteilt werden
				-c false	Event normal verarbeitet
	**************************************************************************/
	virtual BOOLEAN triggerEvent(IEvent* pTriggerEvent);

	/**************************************************************************
	@brief		Queue das �bergebene Event ein, damit es bei trigger() ausgef�hrt wird

	@param[in] IEvent* event	Event das eingef�gt werden soll

	@return		-c true		Event wurde eingef�gt
				-c false	Fehler beim einf�gen
	**************************************************************************/
	virtual BOOLEAN queueEvent(IEvent* pEvent);

	/**************************************************************************
	@brief		Entfernt das erste Event von dem angegebenen Typen aus der EventQueue
				oder alle wenn abortAll = true

	@param[in] CEventType eventType		Typ des Events welches entfernt werden soll
	@param[in] BOOLEAN abortAll			gibt an ob nur das erste oder alle Events 
										des Typen aus der Queue entfernt werden soll

	@return		-c true		Event(s) erfolgreich gel�scht
				-c false	Fehler beim l�schen (keins mehr vorhanden?)
	**************************************************************************/
	virtual BOOLEAN abortEvent(CEventType eventType, BOOLEAN abortAll = false);

	/**************************************************************************
	@brief		F�hrt alle Events in der Event-Queue aus, bis das Zeitlimit 
				erreicht wurde

	@param[in] ULONG timeLimit		Zeitlimit zur Bearbeitung; Nach Ablauf der 
									Zeit werden die �brigen Events verworfen

	@return		-c true		Alle Events verabeitet
				-c false	Nicht alle Events verarbeitet (Timeout)
	**************************************************************************/
	virtual BOOLEAN tick(ULONG timeLimit = INFINITE);

	/**************************************************************************
	@brief		Pr�ft ob der Angegebene EventType von irgendeinem Listener 
				�berhaupt empfangen und damit auch verarbeitet wird

	@param[in] CEventType eventType		EventType der gepr�ft werden soll

	@return		-c true		Event wird verarbeitet
				-c false	Event kann nicht verbeitet werden
	**************************************************************************/
	virtual BOOLEAN validateType(CEventType eventType);

protected:
	// typdefinitionen f�r alle Arten von Maps und Listen die wir brauchen
	typedef vector<IEventListener*> EventListenerList;
	typedef vector<IEventListener*>::iterator EventListenerListIter;
	typedef map<CEventType, EventListenerList> EventListenerMap;
	typedef map<CEventType, EventListenerList>::iterator EventListenerMapIter;
	typedef list<IEvent*> EventQueue;
	typedef list<IEvent*>::iterator EventQueueIter;
	typedef set<CEventType> EventSet;
	typedef set<CEventType>::iterator EventSetIter;

	EventSet mRegisteredEvents;
	EventListenerMap mEventListenerMap;
	
	EventQueue mEventQueue[NUM_EVENT_QUEUES];
	EventQueue* mpReadQueue;
	EventQueue* mpWriteQueue;

	// Zugriff auf die Listener sch�tzen, da auf diese von verschiedenen 
	// Thread zugegriffen werden kann
	CCriticalSection mListenerCS;
	
	// Zugriff auf die WriteQueue sch�tzen, da von verschiedenen Threads Events
	// eingef�gt werden k�nnen. Die ReadQueue muss nicht explizit gesch�tzt 
	// werden, da auf diese nur von diesem Thread aus zugegriffen wird.
	CCriticalSection mWriteQueueCS;
	
};

#endif