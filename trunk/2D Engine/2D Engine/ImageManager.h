#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <map>
using std::map;

#include "ImageResources.h"
#include "Texture.h"
#include "ImageLoader.h"

class CImageManager
{
public:
	CImageManager();
	~CImageManager();

	 BOOLEAN getImage(IMAGE_ID imageId, CTexture* &texture);
	 BOOLEAN releaseImage(IMAGE_ID imageId);

protected:
	VOID initImageMap();
	BOOLEAN loadImage(IMAGE_ID imageId, CTexture*& texture);

protected:
	typedef map<IMAGE_ID, CTexture*> TEXTURE_MAP;
	typedef TEXTURE_MAP::value_type TEXTURE_MAP_TYPE;
	typedef TEXTURE_MAP::iterator TEXTURE_MAP_ITERATOR;
	TEXTURE_MAP mTextures;

	CImageLoader mImageLoader;
};

extern CImageManager gImageManager;

#endif