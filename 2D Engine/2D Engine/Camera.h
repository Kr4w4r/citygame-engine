#ifndef CAMERA_H
#define CAMERA_H

#include "vector2f.h"

typedef struct FRUSTRUM
{
	CVector2f upperLeft;
	CVector2f upperRight;
	CVector2f lowerLeft;
	CVector2f lowerRight;
} T_FRUSTRUM;

class CCamera
{
public:
	CCamera();
	CCamera(float posX, float posY, float width, float height);
	CCamera(CVector2f pos, CVector2f dimension);
	~CCamera();

	VOID setPosition(float x, float y);
	VOID setPosition(CVector2f pos);
	VOID setDimension(float width, float height);
	VOID setDimension(CVector2f dimension);

	CVector2f getPosition();
	CVector2f getDimension();

	T_FRUSTRUM getFrustrum();

protected:
	VOID recalculateFrustrum();

protected:
	CVector2f mPos;
	CVector2f mDimension;

	T_FRUSTRUM mFrustrum;
};

#endif