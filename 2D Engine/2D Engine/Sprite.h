#ifndef SPRITE_H
#define SPRITE_H

#include "TexturedElement.h"

class CSprite : public CTexturedElement
{
public:
	CSprite(CTexture* texture = 0);
	CSprite(float posX, float posY, float width, float height, CTexture* texture = 0);
	CSprite(CVector2f pos, CVector2f dimension, CTexture* texture = 0);
	~CSprite();

	virtual VOID render();

protected:
	virtual void initAnimations() = 0;
};

#endif