#include "ImageManager.h"

CImageManager::CImageManager()
{
	initImageMap();
}

CImageManager::~CImageManager()
{}

VOID CImageManager::initImageMap()
{
	ULONG imageCount = sizeof(gImageResources) / sizeof(T_IMAGE_RESOURCE);

	for (ULONG image = 0; image < imageCount; image++)
	{
		T_IMAGE_RESOURCE resource = gImageResources[image];

		mTextures.insert(TEXTURE_MAP_TYPE(resource.imageId, NULL));
	}
}

BOOLEAN CImageManager::getImage(IMAGE_ID imageId, CTexture *&texture)
{
	TEXTURE_MAP_ITERATOR textureIter = mTextures.find(imageId);
	if (textureIter != mTextures.end())
	{
		// Prüfen ob die Texture bereits geladen wurde
		if ((*textureIter).second == NULL)
		{
			// Texture Laden
			if (loadImage(imageId, texture) == TRUE)
			{
				(*textureIter).second = texture;
			}else
			{
				// Laden fehlgeschlagen
				texture = NULL;
				return FALSE;
			}
		}else
		{
			texture = (*textureIter).second;
		}

		// alles ok
		return TRUE;
	}
	// Fehler beim Holen
	return FALSE;
}

BOOLEAN CImageManager::releaseImage(IMAGE_ID imageId)
{
	TEXTURE_MAP_ITERATOR textureIter = mTextures.find(imageId);
	if (textureIter != mTextures.end())
	{
		CTexture* texture = (*textureIter).second;
		if (texture != NULL)
		{
			if (texture->getReferenceCount() == 0)
			{
				// Textur löschen
				delete texture;
				// Zeiger zurücksetzen
				(*textureIter).second = NULL;

				// Erfolg
				return TRUE;
			}
		}
	}
	// Fehler beim Holen
	return FALSE;
}

BOOLEAN CImageManager::loadImage(IMAGE_ID imageId, CTexture*& texture)
{
	ULONG imageCount = sizeof(gImageResources) / sizeof(T_IMAGE_RESOURCE);

	for (ULONG image = 0; image < imageCount; image++)
	{
		T_IMAGE_RESOURCE resource = gImageResources[image];

		if (resource.imageId == imageId)
		{
			return mImageLoader.loadImage(resource.filePath, texture);
		}
	}	
	return FALSE;
}