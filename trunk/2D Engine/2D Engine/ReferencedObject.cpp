#include "ReferencedObject.h"

ULONG CReferencedObject::msReferencedObjectCount = 0;

CReferencedObject::CReferencedObject()
{
	mReference = ++msReferencedObjectCount;
}

CReferencedObject::~CReferencedObject()
{
}

ULONG CReferencedObject::getReference()
{
	return mReference;
}