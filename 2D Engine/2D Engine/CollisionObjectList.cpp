#include "CollisionObjectList.h"

CCollisionObjectList gCollisionObjectList;

CCollisionObjectList::CCollisionObjectList()
{}

CCollisionObjectList::~CCollisionObjectList()
{}

bool CCollisionObjectList::add(CCollisionObject* object)
{
	mCollisionList.push_back(object);
	return true;
}

bool CCollisionObjectList::remove(CCollisionObject* object)
{
	if (mCollisionList.size() > 0)
	{
		for (COLLISION_OBJECT_LIST_ITER iter = mCollisionList.begin(); iter != mCollisionList.end(); iter++)
		{
			if ((*iter) == object)
			{
				mCollisionList.erase(iter);
				return true;
			}
		}
	}

	return false;
}

/***************************************************
	@brief	Prüft ob das Objekt eine Kollision mit 
			einem anderen Objekt der Liste hat
	
	@param[in] CCollisionObject* checkingObject	zu Prüfendes Object

	@return	bool	true	Kollision gefunden
					false	keine Kollision
***************************************************/
bool CCollisionObjectList::checkCollision(CCollisionObject* checkingObject)
{
	if (mCollisionList.size() > 0)
	{
		for (COLLISION_OBJECT_LIST_ITER iter = mCollisionList.begin(); iter != mCollisionList.end(); iter++)
		{
			if ((*iter) != checkingObject)
			{
				if ((*iter)->checkCollision(checkingObject) == TRUE)
				{
					return true;
				}
				if (checkingObject->checkCollision((*iter)) == TRUE)
				{
					return true;
				}
			}
		}
	}
	return false;
}