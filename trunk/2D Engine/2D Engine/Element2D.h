#ifndef ELEMENT_2D_H
#define ELEMENT_2D_H

#include "ReferencedObject.h"

#include "vector2f.h"

typedef enum RENDERLEVEL
{	
	RENDERLEVEL_BOUNDING_BOX = 1,
	RENDERLEVEL_SPRITE = 2,
	RENDERLEVEL_MAP = 100,
	RENDERLEVEL_UNDEFIND = 1000,
} E_RENDERLEVEL;

class CElement2D : public CReferencedObject
{
public:
	CElement2D(E_RENDERLEVEL renderlevel = RENDERLEVEL_UNDEFIND);
	CElement2D(float posX, float posY, float width, float height, E_RENDERLEVEL renderlevel = RENDERLEVEL_UNDEFIND);
	CElement2D(CVector2f pos, CVector2f dimension, E_RENDERLEVEL renderlevel = RENDERLEVEL_UNDEFIND);
	~CElement2D();

	virtual VOID setPosition(float x, float y);
	virtual VOID setPosition(CVector2f pos);
	virtual VOID setDimension(float width, float height);
	virtual VOID setDimension(CVector2f dimension);
	virtual VOID setRotation(float angle);
	VOID setRenderLevel(E_RENDERLEVEL renderlevel);

	CVector2f getPosition();
	CVector2f getDimension();
	float getRotation();
	E_RENDERLEVEL getRenderLevel();

protected:
	CVector2f mPos;
	CVector2f mDimension;
	float mfAngle;
	E_RENDERLEVEL mRenderlevel;
};

#endif