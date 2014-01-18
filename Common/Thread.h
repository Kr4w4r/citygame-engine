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
	�bergeben k�nnen und �bergeben der Funktion einen Pointer auf unser Objekt.
	
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
	@brief	Stoppt den Thread. Der Thread f�hrt die Ausf�hrung der threadMethod
			noch zu ende und stoppt erst dann! 
			Um den Stoppprozess zu beschleunigen, kann in dem Thread auf die 
			Variable mbStopThread gepr�ft werden.
	**************************************************************************/
	void stopThread();

	/**************************************************************************
	@brief	Gibt zur�ck ob der Thread gestoppt ist oder l�uft.

	@return	BOOLEAN		true, wenn Thread gestoppt ist
						false, wenn Thread l�uft
	**************************************************************************/
	BOOLEAN isStopped();

	/**************************************************************************
	@brief	Bereitet das L�schen des Threadobjetes vor und beendet den Thread.
			Zum pr�fen ob der Thread bereit ist gel�scht zu werden, kann die 
			Methode isReadyForDelete() verwendet werden.
	**************************************************************************/
	void prepareDelete();

	/**************************************************************************
	@brief	Gibt zur�ck ob das Threadobjekt gel�scht werden kann oder nicht.

	@return	BOOLEAN		true, Thread vollst�ndig beendet und bereit zum l�schen
						false, Thread kann noch nicht gel�scht werden.
	**************************************************************************/
	BOOLEAN isReadyForDelete();

private:
	/**************************************************************************
	@brief	Interne Methode welche die Steuerung des Threads �bernimmt und die
			�berschreibbare threadMethod() aufruft.
	**************************************************************************/
	DWORD threadFunction();

protected:
	/**************************************************************************
	@brief	Methode zum ausf�hren von Threadspezifischen Funktionen. Muss von 
			erbenden Klassen �berschrieben werden.
	**************************************************************************/
	virtual void threadMethod() = 0;

protected:
	BOOLEAN mbDeleteThread;
	BOOLEAN mbStopThread;
	BOOLEAN mbStopped;

	DWORD mThreadId;
	HANDLE mThreadHandle;
};
