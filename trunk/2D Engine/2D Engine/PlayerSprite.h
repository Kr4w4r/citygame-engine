#ifndef PLAYER_SPRITE_H
#define PLAYER_SPRITE_H

#include "AnimatedSprite.h"


class CPlayerSprite : public CAnimatedSprite
{
public:
	CPlayerSprite(CTexture* texture = NULL);
	CPlayerSprite(float posX, float posY, float width, float height, CTexture *texture = NULL);
	CPlayerSprite(CVector2f pos, CVector2f dimension, CTexture *texture = NULL);
	~CPlayerSprite();

	VOID setRotation(float angle);

	VOID moveForward(float distance);

protected:
	virtual void initAnimations();

	CVector2f mDirection;
};

#endif