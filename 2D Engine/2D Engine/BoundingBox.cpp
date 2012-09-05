#include "BoundingBox.h"
#include "math.h"
#include "stdio.h"

#include "Element2D.h"

CBoundingBox::CBoundingBox()
{
	mCenter.x = 0;
	mCenter.y = 0;

	mDimension.x = 0;
	mDimension.y = 0;
}

CBoundingBox::~CBoundingBox()
{}

/***********************************************************
@brief		Prüft ob ein Punkt der übergeben Boundingbox 
			innerhalb unserer BoundingBox ist
@param[in]	CBoundingBox& collisionObject	zu prüfende BoundingBox

@return		bool		-\c	true	mindestens ein Punkt liegt innerhalb -> Kollision
						-\c false	keine Kollision
***********************************************************/
bool CBoundingBox::checkCollision(CBoundingBox& collisionObject)
{
	// ersten Punkt prüfen
	CVector2f point = collisionObject.getCenter();
	point.x += (collisionObject.getDimension().x /2);
	point.y += (collisionObject.getDimension().y /2);

	if (isPointInside(point) == true)
	{
		return true;
	}

	point = collisionObject.getCenter();
	point.x -= (collisionObject.getDimension().x /2);
	point.y += (collisionObject.getDimension().y /2);

	if (isPointInside(point) == true)
	{
		return true;
	}

	point = collisionObject.getCenter();
	point.x -= (collisionObject.getDimension().x /2);
	point.y -= (collisionObject.getDimension().y /2);

	if (isPointInside(point) == true)
	{
		return true;
	}

	point = collisionObject.getCenter();
	point.x += (collisionObject.getDimension().x /2);
	point.y -= (collisionObject.getDimension().y /2);

	if (isPointInside(point) == true)
	{
		return true;
	}

	// keine Kollision
	return false;
}

bool CBoundingBox::isPointInside(CVector2f point)
{
	if (fabs(mCenter.x - point.x) > (mDimension.x /2))
	{
		return false;
	}

    if (fabs(mCenter.y - point.y) > (mDimension.y /2))
	{
		return false;
	}
	return true;
}

CVector2f CBoundingBox::getCenter()
{
	return mCenter;
}

CVector2f CBoundingBox::getDimension()
{
	return mDimension;
}

void CBoundingBox::setCenter(CVector2f center)
{
	mCenter = center;
}

void CBoundingBox::setDimension(CVector2f dimension)
{
	mDimension = dimension;
}

void CBoundingBox::render()
{
	glPushMatrix();

	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0f, 1.0f, 1.0f);

//	glLineWidth(2);

	glBegin(GL_LINES);
		glVertex3f(mCenter.x + (mDimension.x /2), mCenter.y + (mDimension.y /2), RENDERLEVEL_BOUNDING_BOX);
		glVertex3f(mCenter.x - (mDimension.x /2), mCenter.y + (mDimension.y /2), RENDERLEVEL_BOUNDING_BOX);
		
		glVertex3f(mCenter.x - (mDimension.x /2), mCenter.y + (mDimension.y /2), RENDERLEVEL_BOUNDING_BOX);
		glVertex3f(mCenter.x - (mDimension.x /2), mCenter.y - (mDimension.y /2), RENDERLEVEL_BOUNDING_BOX);
		
		glVertex3f(mCenter.x - (mDimension.x /2), mCenter.y - (mDimension.y /2), RENDERLEVEL_BOUNDING_BOX);
		glVertex3f(mCenter.x + (mDimension.x /2), mCenter.y - (mDimension.y /2), RENDERLEVEL_BOUNDING_BOX);
		
		glVertex3f(mCenter.x + (mDimension.x /2), mCenter.y - (mDimension.y /2), RENDERLEVEL_BOUNDING_BOX);
		glVertex3f(mCenter.x + (mDimension.x /2), mCenter.y + (mDimension.y /2), RENDERLEVEL_BOUNDING_BOX);
	glEnd();

	glPopMatrix();
}