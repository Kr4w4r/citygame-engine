#include "Thread.h"

#include <stdio.h>

DWORD WINAPI threadCaller(__in  LPVOID lpParameter)
{
	CThread* thread = (CThread*)lpParameter;
	return thread->threadFunction();
}

CThread::CThread(const CHAR* threadName, SIZE_T stacksize, BOOLEAN bStartSuspended)
{
	mbDeleteThread = FALSE;
	mbStopped = bStartSuspended;
	mbStopThread = FALSE;

	DWORD createFlags = 0;
	if (bStartSuspended == TRUE)
	{
		createFlags |= CREATE_SUSPENDED;
	}
	
	mThreadHandle = CreateThread(NULL, stacksize, &threadCaller, this, createFlags, &mThreadId);

	if (mThreadHandle == INVALID_HANDLE_VALUE)
	{
		char out[100];
		sprintf_s(out, 100, "Creating Thread: %s %u failed.\n", threadName, mThreadId);
		OutputDebugString(out);
	}
}

CThread::~CThread()
{
	if (mThreadHandle != INVALID_HANDLE_VALUE)
	{
		// sollte die Vorbereitung des Löschens noch nicht eingeleitet sein
		// machen müssen wir das jetzt machen. Es ist besser wenn man das
		// nicht im Konstrukor macht, da es zu einer Unterbrechung des Aufrufenden 
		// Threads kommen kann, wenn der Thread hier noch nicht fertig ist.
		if (mbDeleteThread == FALSE)
		{
			// also vorbereiten und warten bis der Thread bereit ist
			prepareDelete();
			while (isReadyForDelete() == FALSE)
			{
				Sleep(1);
			}
		}

		// das Handle freigeben und dann ist alles toll
		if (CloseHandle(mThreadHandle) == TRUE)
		{
			mThreadHandle = INVALID_HANDLE_VALUE;
		}
	}
}

DWORD CThread::threadFunction()
{
	while (1)
	{
		while (mbStopThread == FALSE)
		{
			mbStopped = FALSE;
			threadMethod();
		}
		// der Thread ist jetzt gestoppt
		mbStopped = TRUE;

		// wenn der Thread gelöscht werden soll, lassen wir diesen auslaufen
		if (mbDeleteThread == TRUE)
		{
			ExitThread(0);
		}
		// den Thread unterbrechen
		SuspendThread(mThreadHandle);
	}
	ExitThread(0);
}

void CThread::trigger()
{
	// wir fahren mit dem Ablauf des Threads nur fort wenn der Thread gestoppt 
	// ist und wir nicht gerade dabei sind diesen zu löschen
	if ((mbStopped == TRUE) && (mbDeleteThread == FALSE))
	{
		mbStopThread = FALSE;
		ResumeThread(mThreadHandle);
	}
}

void CThread::stopThread()
{
	mbStopThread = TRUE;
}

BOOLEAN CThread::isStopped()
{
	return mbStopped;
}

void CThread::prepareDelete()
{
	if (mThreadHandle != INVALID_HANDLE_VALUE)
	{
		// Der Thread soll ordentlich runtergefahren werden dazu den Thread erstmal 
		// bekanntgeben, dass wir schluss machen wollen und verhindern das der Thread 
		// wieder getriggert wird
		mbDeleteThread = TRUE;
		stopThread();
	}
}

BOOLEAN CThread::isReadyForDelete()
{
	if (mbDeleteThread == TRUE)
	{
		if (isStopped() == TRUE)
		{
			return TRUE;
		}
	}
	return FALSE;
}