#pragma once

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "CriticalSection.h"

DWORD WINAPI threadCaller(__in  LPVOID lpParameter);

class CThread
{
	/**************************************************************************
	Ein Thread braucht einen Pointer auf eine statische Funktion und kann nicht
	mit dem Pointer auf die Methode eines Objektes umgehen. Darum haben wir 
	eine externe Statische C-Funktion dessen Pointer wir dem erzeugten Thread 
	übergeben können und übergeben der Funktion einen Pointer auf unser Objekt.
	
	Damit diese Funktion auf die private deklarierte Methode threadFunction()
	zugreifen kann, muss die externe C-Funktion als Friend deklariert werden.
	**************************************************************************/
	friend DWORD WINAPI threadCaller(__in  LPVOID lpParameter);

public:
	CThread(const CHAR* threadName, SIZE_T stacksize = 0, BOOLEAN bStartSuspended = FALSE);
	virtual ~CThread();

	/**************************************************************************
	@brief	Falls der Thread gestoppt ist, wird dieser jetzt gestartet.
	**************************************************************************/
	void trigger();

	/**************************************************************************
	@brief	Stoppt den Thread. Der Thread führt die Ausführung der threadMethod
			noch zu ende und stoppt erst dann! 
			Um den Stoppprozess zu beschleunigen, kann in dem Thread auf die 
			Variable mbStopThread geprüft werden.
	**************************************************************************/
	void stopThread();

	/**************************************************************************
	@brief	Gibt zurück ob der Thread gestoppt ist oder läuft.

	@return	BOOLEAN		true, wenn Thread gestoppt ist
						false, wenn Thread läuft
	**************************************************************************/
	BOOLEAN isStopped();

	/**************************************************************************
	@brief	Bereitet das Löschen des Threadobjetes vor und beendet den Thread.
			Zum prüfen ob der Thread bereit ist gelöscht zu werden, kann die 
			Methode isReadyForDelete() verwendet werden.
	**************************************************************************/
	void prepareDelete();

	/**************************************************************************
	@brief	Gibt zurück ob das Threadobjekt gelöscht werden kann oder nicht.

	@return	BOOLEAN		true, Thread vollständig beendet und bereit zum löschen
						false, Thread kann noch nicht gelöscht werden.
	**************************************************************************/
	BOOLEAN isReadyForDelete();

private:
	/**************************************************************************
	@brief	Interne Methode welche die Steuerung des Threads übernimmt und die
			überschreibbare threadMethod() aufruft.
	**************************************************************************/
	DWORD threadFunction();

protected:
	/**************************************************************************
	@brief	Methode zum ausführen von Threadspezifischen Funktionen. Muss von 
			erbenden Klassen überschrieben werden.
	**************************************************************************/
	virtual void threadMethod() = 0;

protected:
	BOOLEAN mbDeleteThread;
	BOOLEAN mbStopThread;
	BOOLEAN mbStopped;

	DWORD mThreadId;
	HANDLE mThreadHandle;
};
