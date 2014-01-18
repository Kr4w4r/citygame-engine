#ifndef IEVENT_H
#define IEVENT_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include <string>
using std::string;

class CEventType
{
public:
	CEventType(string name)
	{
		mName = name;
	};

	~CEventType() {};

	string getName() const { return mName; };

	bool operator ==(CEventType const& compare) const
	{
		if (mName == compare.getName())
		{
			return true;
		}
		return false;
	}

	bool operator <(CEventType const& checkBigger) const
	{
		return (getName().compare(checkBigger.getName()) < 0);
	}

protected:
	string mName;
};



class IEvent
{
public:
	virtual ~IEvent() {};

	virtual const CEventType& getType() const = 0;
	virtual ULONG getTimestamp() = 0;
};

#endif