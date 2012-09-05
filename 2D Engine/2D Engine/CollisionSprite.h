#ifndef COLLISION_SPRITE_H
#define COLLISION_SPRITE_H

#include "Sprite.h"
#include "CollisionObject.h"

class CCollisionSprite : public CSprite, public CCollisionObject
{
public:
	CCollisionSprite(CTexture* texture = 0);
	CCollisionSprite(float posX, float posY, float width, float height, CTexture* texture = 0);
	CCollisionSprite(CVector2f pos, CVector2f dimension, CTexture* texture = 0);
	~CCollisionSprite();

	VOID setPosition(float x, float y);
	VOID setPosition(CVector2f pos);
	VOID setDimension(float width, float height);
	VOID setDimension(CVector2f dimension);
	VOID setRotation(float angle);

protected:
	VOID recalculateBoundingBoxDimension();
};

#endif