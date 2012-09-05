#ifndef NOT_MOVEABLE_TILE_H
#define NOT_MOVEABLE_TILE_H

#include "Tile.h"
#include "CollisionObject.h"

class CNotMoveableTile : public CTile, public CCollisionObject
{
public:
	CNotMoveableTile(float x, float y, float width, float height, CTexture* texture = NULL);
	~CNotMoveableTile();

	virtual void render() 
	{
		CTile::render();
		mBoundingBox.render();
	};
};

#endif