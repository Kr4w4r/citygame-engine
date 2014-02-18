#pragma once

#include "vector3f.h"

class C3DCamera
{
public:
	C3DCamera();
	virtual ~C3DCamera();

	CVector3f getPosition() {return mPosition; };
	CVector3f getRotation() {return mRotation; };

	CVector3f setPosition(CVector3f position) { mPosition = position; };
	CVector3f setRotation(CVector3f rotation) { mRotation = rotation; };

	void translateX(float distance) { mPosition.x += distance; };
	void translateY(float distance) { mPosition.y += distance; };
	void translateZ(float distance) { mPosition.z += distance; };

	void rotateX(float angle) { mRotation.x += angle; };
	void rotateY(float angle) { mRotation.y += angle; };
	void rotateZ(float angle) { mRotation.z += angle; };

	void lookAt(CVector3f position);

	void render();

protected:
	CVector3f mPosition;
	CVector3f mRotation;

	CVector3f mLook;
	CVector3f mUp;
	CVector3f mRight;
};