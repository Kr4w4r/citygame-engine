#include "Sprite.h"

CSprite::CSprite(CTexture *texture)
: CTexturedElement(RENDERLEVEL_SPRITE, texture)
{}

CSprite::CSprite(float posX, float posY, float width, float height, CTexture *texture)
: CTexturedElement(posX, posY, width, height, RENDERLEVEL_SPRITE, texture)
{}

CSprite::CSprite(CVector2f pos, CVector2f dimension, CTexture *texture)
: CTexturedElement(pos, dimension, RENDERLEVEL_SPRITE, texture)
{}

CSprite::~CSprite()
{
}

VOID CSprite::render()
{
	CTexturedElement::render();
}