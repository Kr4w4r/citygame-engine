#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "Texture.h"

typedef struct TGA_HEADER
{
	GLubyte	ID_Length;
	GLubyte colorMapType;
	GLubyte imageType;
	GLubyte colorMapSpecification[5];
	GLshort xOrigin;
	GLshort yOrigin;
	GLshort imageWidth;
	GLshort imageHeight;
	GLubyte pixelDepth; 
} T_TGA_HEADER;

class CImageLoader
{
public:
	CImageLoader();
	~CImageLoader();

	BOOLEAN loadImage(CHAR* filePath, CTexture*& texture);

protected:
	CTexture* loadTGA(CHAR* filePath);
};

#endif