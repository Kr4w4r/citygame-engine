#ifndef THREAD_H
#define THREAD_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

DWORD WINAPI threadCaller(__in  LPVOID lpParameter);

class CThread
{
	friend DWORD WINAPI threadCaller(__in  LPVOID lpParameter);

public:
	CThread(CHAR* threadName, SIZE_T stacksize = 0, BOOLEAN bStartSuspended = FALSE);
	virtual ~CThread();

	void trigger();
	void stopThread();

	BOOLEAN isStopped();

	void prepareDelete();
	BOOLEAN isReadyForDelete();

private:
	DWORD threadFunction();

protected:
	virtual void threadMethode() = 0;

	BOOLEAN mbDeleteThread;
	BOOLEAN mbStopThread;
	BOOLEAN mbStopped;

	DWORD mThreadId;
	HANDLE mThreadHandle;
};

#endif