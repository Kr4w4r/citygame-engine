#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "gl/gl.h"
#include "gl/glu.h"

#include "vector2f.h"
#include "IRenderable.h"

class CBoundingBox : public IRenderable
{
public:
	CBoundingBox();
	~CBoundingBox();

	/***********************************************************
	@brief		Prüft ob ein Punkt der übergeben Boundingbox 
				innerhalb unserer BoundingBox ist
	@param[in]	CBoundingBox& collisionObject	zu prüfende BoundingBox

	@return		bool		-\c	true	mindestens ein Punkt liegt innerhalb -> Kollision
							-\c false	keine Kollision
	***********************************************************/
	bool checkCollision(CBoundingBox& collisionObject);
	bool isPointInside(CVector2f point);

	CVector2f getCenter();
	CVector2f getDimension();

	void setCenter(CVector2f center);
	void setDimension(CVector2f dimension);

	void render();

protected:
	CVector2f mCenter;
	CVector2f mDimension;
};

#endif