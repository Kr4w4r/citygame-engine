#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>
using std::string;

class CCriticalSection
{
public:
	CCriticalSection(string debugName)
	{
		locks = 0;
		mDebugName = debugName;
		InitializeCriticalSection(&mCS);
	}

	virtual ~CCriticalSection()
	{
		DeleteCriticalSection(&mCS);
	}

	/**************************************************************************
	@brief	Betritt die CriticalSection. Falls diese bereits verwendet wird, 
			warten wir bis diese frei wird.
	**************************************************************************/
	void enter()
	{
		EnterCriticalSection(&mCS);
		locks++;
	}

	/**************************************************************************
	@brief	Versucht die CriticalSectoin zu betreten. Sollte diese bereits 
			verwendet werden, gibt der Aufruf FALSE zurück. Sonst wird die 
			Critical Section betreten.
	**************************************************************************/
	BOOLEAN tryEnter()
	{
		return TryEnterCriticalSection(&mCS);
	}
	
	/**************************************************************************
	@brief	Verlässt die CriticalSection. Falls diese bereits verwendet wird, 
			warten wir bis diese frei wird.
	**************************************************************************/
	void leave()
	{
		locks--;
		LeaveCriticalSection(&mCS);
	}

protected:
	CRITICAL_SECTION mCS;
	ULONG locks;
	string mDebugName;
};

class CCriticalBlock
{
public:
	CCriticalBlock(CCriticalSection* pCritSect)
	{
		mpCS = pCritSect;
		mpCS->enter();
	}

	virtual ~CCriticalBlock()
	{
		mpCS->leave();
	}

protected:
	CCriticalSection* mpCS;
};