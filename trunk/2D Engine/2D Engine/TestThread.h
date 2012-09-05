#ifndef TEST_THREAD_H
#define TEST_THREAD_H

#include "Thread.h"

class CTestThread : public CThread
{
public:
	CTestThread() : CThread("TestThread")
	{};

	virtual ~CTestThread() 
	{
		CThread::~CThread();
	};

	virtual void threadMethode()
	{
		CHAR out[100];
		sprintf(out, "ThreadMethode: %u\n", mThreadId);
		OutputDebugString(out);
		Sleep(200);
	};
};

#endif