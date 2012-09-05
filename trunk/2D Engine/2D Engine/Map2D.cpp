#include "Map2D.h"
#include "NotmoveableTile.h"

CMap2D::CMap2D()
{
	mWidth = 0;
	mHeight = 0;
	mTileSize = 1.0f;

	mTiles = NULL;
}

CMap2D::CMap2D(GLuint width, GLuint height, GLfloat tileSize)
{
	mWidth = width;
	mHeight = height;
	
	mTileSize = tileSize;
	if (tileSize == 0)
	{
		mTileSize = 1.0f;
	}

	CTexture* pTexture = NULL;

	if ((mWidth != 0) && (mHeight != 0))
	{
		mTiles = new CTile*[width * height];

		for (GLuint y = 0; y < mHeight; y++)
		{
			for (GLuint x = 0; x < mWidth; x++)
			{
				//GLfloat posX = (-(GLfloat)mWidth * mTileSize / 2) + x;
				//GLfloat posY = ((GLfloat)mHeight * mTileSize / 2) - y;

				GLfloat posX = ((GLfloat)x - (mWidth /2)) * mTileSize;
				GLfloat posY = -((GLfloat)y - (mWidth /2)) * mTileSize;

				posX += mTileSize /2;
				posY += mTileSize /2;

				pTexture = NULL;
				gImageManager.getImage(IMAGE_GRASS_TILE, pTexture);

				mTiles[y * mWidth + x] = new CTile(posX + mTileSize /2, posY - mTileSize /2, mTileSize, mTileSize, pTexture);
			}
		}
	}else
	{
		mTiles = NULL;
	}
}

CMap2D::CMap2D(char *mapPath)
{
	// Todo
}

CMap2D::~CMap2D()
{
	if (mTiles != NULL)
	{
		for (GLuint y = 0; y < mHeight; y++)
		{
			for (GLuint x = 0; x < mWidth; x++)
			{
				if (mTiles[y * mWidth + x] != NULL)
				{
					delete mTiles[y * mWidth + x];
				}
			}
		}

		delete []mTiles;
	}
}

void CMap2D::render()
{
	if (mTiles != NULL)
	{
		for (GLuint y = 0; y < mWidth; y++)	
		{
			for (GLuint x = 0; x < mWidth; x++)
			{
				if (mTiles[y * mWidth + x] != NULL)
				{
					mTiles[y * mWidth + x]->render();
				}
			}
		}
	}
}

bool CMap2D::getTile(GLuint x, GLuint y, CTile*& tile)
{
	if ((x < mWidth) && (y < mHeight))
	{
		tile = mTiles[y * mWidth + x];
		return true;
	}

	return false;
}

bool CMap2D::setTile(GLuint x, GLuint y, bool moveable, CTexture* pTexture)
{
	CVector2f pos;

	if (mTiles[y * mWidth + x] != NULL)
	{
		pos = mTiles[y * mWidth + x]->getPosition();
		delete mTiles[y * mWidth + x];
		mTiles[y * mWidth + x] = NULL;
	}

	if ((x < mWidth) && (y < mHeight))
	{
		if (moveable == TRUE)
		{
			mTiles[y * mWidth + x] = new CTile(pos.x, pos.y, mTileSize, mTileSize, pTexture);
		}else
		{
			mTiles[y * mWidth + x] = new CNotMoveableTile(pos.x, pos.y, mTileSize, mTileSize, pTexture);
		}
		return true;
	}

	return false;
}

bool CMap2D::getSize(GLuint &x, GLuint &y)
{
	x = mWidth;
	y = mHeight;
	return true;
}