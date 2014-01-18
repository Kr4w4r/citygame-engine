#pragma once

#include "Event.h"

class CKeyboardEvent : public CEvent
{
public:
	CKeyboardEvent(CHAR key, BOOLEAN bDown);
	virtual ~CKeyboardEvent();

	virtual const CEventType& getType() const;

	const CHAR getKeyPressed() { return mKeyPressed; };
	const CHAR isKeyDown() { return mbDown; };

public:
	static const CEventType msEventType;

protected:
	const CHAR mKeyPressed;
	const BOOLEAN mbDown;
};