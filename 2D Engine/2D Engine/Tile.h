#ifndef TILE_H
#define TILE_H

#include "TexturedElement.h"

class CTile : public CTexturedElement
{
public:
	CTile(float x, float y, float width, float height, CTexture* texture = NULL);
	~CTile();

	virtual void render();
};

#endif