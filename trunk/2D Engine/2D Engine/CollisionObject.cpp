#include "CollisionObject.h"
#include "CollisionObjectList.h"

extern CCollisionObjectList gCollisionObjectList;

CCollisionObject::CCollisionObject()
{
	gCollisionObjectList.add(this);
}

CCollisionObject::~CCollisionObject()
{
	gCollisionObjectList.remove(this);
}

bool CCollisionObject::checkCollision(CCollisionObject* collisionObj)
{
	return mBoundingBox.checkCollision(collisionObj->getBoundingBox());
}

CBoundingBox CCollisionObject::getBoundingBox()
{
	return mBoundingBox;
}