#include "NotMoveableTile.h"

CNotMoveableTile::CNotMoveableTile(float x, float y, float width, float height, CTexture* texture)
:CTile(x, y, width, height, texture)
{
	mBoundingBox.setCenter(CVector2f(x,y));
	mBoundingBox.setDimension(CVector2f(width, height));
}

CNotMoveableTile::~CNotMoveableTile()
{}