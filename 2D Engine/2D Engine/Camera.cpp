#include "Camera.h"

CCamera::CCamera()
{}

CCamera::CCamera(float posX, float posY, float width, float height)
{
	mPos.x = posX;
	mPos.y = posY;
	mDimension.x = width;
	mDimension.y = height;
}

CCamera::CCamera(CVector2f pos, CVector2f dimension)
{
	mPos = pos;
	mDimension = dimension;
}

CCamera::~CCamera()
{}

VOID CCamera::setPosition(float x, float y)
{
	mPos.x = x;
	mPos.y = y;

	recalculateFrustrum();
}

VOID CCamera::setPosition(CVector2f pos)
{
	mPos = pos;

	recalculateFrustrum();
}

VOID CCamera::setDimension(float width, float height)
{
	mDimension.x = width;
	mDimension.y = height;

	recalculateFrustrum();
}

VOID CCamera::setDimension(CVector2f dimension)
{
	mDimension = dimension;

	recalculateFrustrum();
}

CVector2f CCamera::getPosition()
{
	return mPos;
}

CVector2f CCamera::getDimension()
{
	return mDimension;
}

T_FRUSTRUM CCamera::getFrustrum()
{
	return mFrustrum;
}

VOID CCamera::recalculateFrustrum()
{
	mFrustrum.upperLeft.x = mPos.x - (mDimension.x /2);
	mFrustrum.upperLeft.y = mPos.y + (mDimension.y /2);

	mFrustrum.upperRight.x = mPos.x + (mDimension.x /2);
	mFrustrum.upperRight.y = mPos.y + (mDimension.y /2);

	mFrustrum.lowerLeft.x = mPos.x - (mDimension.x /2);
	mFrustrum.lowerLeft.y = mPos.y - (mDimension.y /2);

	mFrustrum.lowerRight.x = mPos.x + (mDimension.x /2);
	mFrustrum.lowerRight.y = mPos.y - (mDimension.y /2);
}