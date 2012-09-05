#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "IEventManager.h"

#include <set>
#include <vector>
#include <list>
#include <map>
using namespace std;

const UCHAR NUM_EVENT_QUEUES = 2;

class CEventManager : public IEventManager
{
protected:
	// protected Konstruktor da singleton Klasse
	CEventManager();
public:
	~CEventManager();

	// Zugriff auf Singleton
	static IEventManager* getInstance();

	// Methoden für Eventlistener
	virtual void addEventListener(IEventListener* pEventListener, EVENT_TYPE triggerType);
	virtual void deleteEventListener(IEventListener* pEventListener, EVENT_TYPE triggerType);
	virtual void deleteEventListener(IEventListener* pEventListener);

	// Methoden für Events

	/**************************************************************************
	@brief		Triggert alle Listener für das Event genau JETZT

	@param[in] IEvent* event	Event das ausgeführt werden soll

	@return		-c true		Event verbraucht und sollte NICHT weiterverteilt werden
				-c false	Event normal verarbeitet
	**************************************************************************/
	virtual BOOLEAN triggerEvent(IEvent* pTriggerEvent);

	/**************************************************************************
	@brief		Queue das übergebene Event ein, damit es bei trigger() ausgeführt wird

	@param[in] IEvent* event	Event das eingefügt werden soll

	@return		-c true		Event wurde eingefügt
				-c false	Fehler beim einfügen
	**************************************************************************/
	virtual BOOLEAN queueEvent(IEvent* pEvent);

	/**************************************************************************
	@brief		Entfernt das erste Event von dem angegebenen Typen aus der EventQueue
				oder alle wenn abortAll = true

	@param[in] EVENT_TYPE eventType		Typ des Events welches entfernt werden soll
	@param[in] BOOLEAN abortAll			gibt an ob nur das erste oder alle Events 
										des Typen aus der Queue entfernt werden soll

	@return		-c true		Event(s) erfolgreich gelöscht
				-c false	Fehler beim löschen (keins mehr vorhanden?)
	**************************************************************************/
	virtual BOOLEAN abortEvent(EVENT_TYPE eventType, BOOLEAN abortAll = false);

	/**************************************************************************
	@brief		Führt alle Events in der Event-Queue aus, bis das Zeitlimit 
				erreicht wurde

	@param[in] ULONG timeLimit		Zeitlimit zur Bearbeitung; Nach Ablauf der 
									Zeit werden die übrigen Events verworfen

	@return		-c true		Alle Events verabeitet
				-c false	Nicht alle Events verarbeitet (Timeout)
	**************************************************************************/
	virtual BOOLEAN tick(ULONG timeLimit = INFINITE);

	/**************************************************************************
	@brief		Prüft ob der Angegebene EventType von irgendeinem Listener 
				überhaupt empfangen und damit auch verarbeitet wird

	@param[in] EVENT_TYPE eventType		EventType der geprüft werden soll

	@return		-c true		Event wird verarbeitet
				-c false	Event kann nicht verbeitet werden
	**************************************************************************/
	virtual BOOLEAN validateType(EVENT_TYPE eventType);

protected:
	// typdefinitionen für alle Arten von Maps und Listen die wir brauchen
	typedef vector<IEventListener*> EventListenerList;
	typedef map<EVENT_TYPE, EventListenerList> EventListenerMap;
	typedef list<IEvent*> EventQueue;
	typedef set<EVENT_TYPE> EventSet;

	EventSet mRegisteredEvents;
	EventListenerMap mEventListenerMap;
	
	EventQueue mEventQueue[NUM_EVENT_QUEUES];
	EventQueue* mpReadQueue;
	EventQueue* mpWriteQueue;
};

#endif