#ifndef COLLISION_OBJECT_LIST_H
#define COLLISION_OBJECT_LIST_H

#include <vector>
using std::vector;

#include "CollisionObject.h"

class CCollisionObjectList
{
public:
	CCollisionObjectList();
	~CCollisionObjectList();

	bool add(CCollisionObject* object);
	bool remove(CCollisionObject* object);

	/***************************************************
		@brief	Pr�ft ob das Objekt eine Kollision mit 
				einem anderen Objekt der Liste hat (es werden alle gepr�ft)
		
		@param[in] CCollisionObject* checkingObject	zu Pr�fendes Object

		@return	bool	true	Kollision gefunden
						false	keine Kollision
	***************************************************/
	bool checkCollision(CCollisionObject* checkingObject);

protected:
	typedef vector<CCollisionObject*> COLLISION_OBJECT_LIST;
	typedef COLLISION_OBJECT_LIST::iterator COLLISION_OBJECT_LIST_ITER;

	COLLISION_OBJECT_LIST mCollisionList;
};

extern CCollisionObjectList gCollisionObjectList;

#endif