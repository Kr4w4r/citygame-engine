#include "CollisionSprite.h"
#include "mathMacros.h"

CCollisionSprite::CCollisionSprite(CTexture* texture)
:CSprite(texture)
{}

CCollisionSprite::CCollisionSprite(float posX, float posY, float width, float height, CTexture* texture)
:CSprite(posX, posY, width, height, texture)
{
	mBoundingBox.setCenter(mPos);
	mBoundingBox.setDimension(mDimension);
}

CCollisionSprite::CCollisionSprite(CVector2f pos, CVector2f dimension, CTexture* texture)
:CSprite(pos, dimension, texture)
{
	mBoundingBox.setCenter(mPos);
	mBoundingBox.setDimension(mDimension);
}

CCollisionSprite::~CCollisionSprite()
{}

VOID CCollisionSprite::setPosition(float x, float y)
{
	CSprite::setPosition(x, y);
	mBoundingBox.setCenter(mPos);
}

VOID CCollisionSprite::setPosition(CVector2f pos)
{
	CSprite::setPosition(pos);
	mBoundingBox.setCenter(mPos);
}

VOID CCollisionSprite::setDimension(float width, float height)
{
	CSprite::setDimension(width, height);

	recalculateBoundingBoxDimension();
}

VOID CCollisionSprite::setDimension(CVector2f dimension)
{
	CSprite::setDimension(dimension);
	
	recalculateBoundingBoxDimension();
}

VOID CCollisionSprite::setRotation(float angle)
{
	CSprite::setRotation(angle);

	// ausdehnung der AABB neu berechnen
	recalculateBoundingBoxDimension();	
}

VOID CCollisionSprite::recalculateBoundingBoxDimension()
{
	CVector2f corner1;
	CVector2f corner2;
	CVector2f corner3;
	CVector2f corner4;
	
	corner1.x = cos(DEG(mfAngle)) * (mDimension.x ) - sin(DEG(mfAngle)) * (mDimension.y );
	corner1.y = sin(DEG(mfAngle)) * (mDimension.x ) + cos(DEG(mfAngle)) * (mDimension.y );

	corner2.x = cos(DEG(mfAngle)) * (-mDimension.x) - sin(DEG(mfAngle)) * (mDimension.y );
	corner2.y = sin(DEG(mfAngle)) * (-mDimension.x) + cos(DEG(mfAngle)) * (mDimension.y );

	corner3.x = cos(DEG(mfAngle)) * (-mDimension.x) - sin(DEG(mfAngle)) * (-mDimension.y );
	corner3.y = sin(DEG(mfAngle)) * (-mDimension.x) + cos(DEG(mfAngle)) * (-mDimension.y );

	corner4.x = cos(DEG(mfAngle)) * (mDimension.x ) - sin(DEG(mfAngle)) * (-mDimension.y );
	corner4.y = sin(DEG(mfAngle)) * (mDimension.x ) + cos(DEG(mfAngle)) * (-mDimension.y );

	// obere Begrenzung finden
	float upperBound = MAX(corner1.x, corner2.x);
	upperBound = MAX(upperBound, corner3.x);
	upperBound = MAX(upperBound, corner4.x);

	// untere Begrenzung finden ( == -obere)

	// linke Begrenzung finden
	float sideBound = MAX(corner1.y, corner2.y);
	sideBound = MAX(sideBound, corner3.y);
	sideBound = MAX(sideBound, corner4.y);

	// rechte Begrenzung finden ( == -linke)

	mBoundingBox.setDimension(CVector2f(upperBound, sideBound));
}