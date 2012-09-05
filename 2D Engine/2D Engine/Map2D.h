#ifndef MAP2D_H
#define MAP2D_H

#include "IRenderable.h"

#include "Tile.h"

class CMap2D : public IRenderable
{
public:
	CMap2D();
	CMap2D(GLuint width, GLuint height, GLfloat tileSize);
	CMap2D(char* mapPath);
	~CMap2D();

	virtual void render();

	bool getTile(GLuint x, GLuint y, CTile*& tile);
	bool setTile(GLuint x, GLuint y, bool moveable, CTexture* pTexture);

	bool getSize(GLuint& x, GLuint& y);

protected:
	GLuint mWidth;
	GLuint mHeight;
	GLfloat mTileSize;
	CTile** mTiles;
};

#endif