#ifndef REFERENCED_OBJECT_H
#define REFERENCED_OBJECT_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

class CReferencedObject
{
public:
	CReferencedObject();
	~CReferencedObject();

	ULONG getReference();

private:
	ULONG mReference;

	static ULONG msReferencedObjectCount;
};

#endif