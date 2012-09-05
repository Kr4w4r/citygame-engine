#include "Element2D.h"

CElement2D::CElement2D(E_RENDERLEVEL renderlevel)
{
	mPos.x = 0;
	mPos.y = 0;
	mDimension.x = 0;
	mDimension.y = 0;
	mfAngle = 0;

	mRenderlevel = renderlevel;
}

CElement2D::CElement2D(float posX, float posY, float width, float height, E_RENDERLEVEL renderlevel)
{
	mPos.x = posX;
	mPos.y = posY;
	mDimension.x = width;
	mDimension.y = height;
	mfAngle = 0;
	mRenderlevel = renderlevel;
}

CElement2D::CElement2D(CVector2f pos, CVector2f dimension, E_RENDERLEVEL renderlevel)
{
	mPos = pos;
	mDimension = dimension;
	mfAngle = 0;
	mRenderlevel = renderlevel;
}

CElement2D::~CElement2D()
{
}

CVector2f CElement2D::getPosition()
{
	return mPos;
}

CVector2f CElement2D::getDimension()
{
	return mDimension;
}

float CElement2D::getRotation()
{
	return mfAngle;
}

E_RENDERLEVEL CElement2D::getRenderLevel()
{
	return mRenderlevel;
}

VOID CElement2D::setPosition(float x, float y)
{
	mPos.x = x;
	mPos.y = y;
}

VOID CElement2D::setPosition(CVector2f pos)
{
	mPos = pos;
}

VOID CElement2D::setDimension(float width, float height)
{
	mDimension.x = width;
	mDimension.y = height;
}

VOID CElement2D::setDimension(CVector2f dimension)
{
	mDimension = dimension;
}

VOID CElement2D::setRotation(float angle)
{
	mfAngle = angle;
	if (mfAngle > 360)
	{
		mfAngle -= 360;
	}
	if (mfAngle < 0)
	{
		mfAngle += 360;
	}
}

VOID CElement2D::setRenderLevel(E_RENDERLEVEL renderlevel)
{
	mRenderlevel = renderlevel;
}
