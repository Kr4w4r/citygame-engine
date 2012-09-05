#ifndef TEXTURED_ELEMENT_H
#define TEXTURED_ELEMENT_H

#include "IRenderable.h"
#include "Element2D.h"
#include "Texture.h"
#include "ImageManager.h"

class CTexturedElement : public IRenderable, public CElement2D
{
public:
	CTexturedElement(E_RENDERLEVEL renderlevel = RENDERLEVEL_UNDEFIND, CTexture* texture = NULL);
	CTexturedElement(float posX, float posY, float width, float height, E_RENDERLEVEL renderlevel = RENDERLEVEL_UNDEFIND, CTexture* texture = 0);
	CTexturedElement(CVector2f pos, CVector2f dimension, E_RENDERLEVEL renderlevel = RENDERLEVEL_UNDEFIND, CTexture* texture = 0);
	~CTexturedElement();

	VOID setTexture(CTexture* texture);
	CTexture* getTexture();

	virtual VOID render();

protected:
	CTexture* mTexture;
};

#endif