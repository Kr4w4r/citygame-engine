#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include "BoundingBox.h"

class CCollisionObject
{
public:
	CCollisionObject();
	~CCollisionObject();

	bool checkCollision(CCollisionObject* collisionObj);

	CBoundingBox getBoundingBox();

protected:
	CBoundingBox mBoundingBox;
};

#endif