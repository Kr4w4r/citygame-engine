#include "ImageLoader.h"

#include "windows.h"

#include <fstream>
using std::ifstream;

extern CHAR gExeFilePath[MAX_PATH];

CImageLoader::CImageLoader()
{}

CImageLoader::~CImageLoader()
{}

BOOLEAN CImageLoader::loadImage(CHAR* filePath, CTexture*& texture)
{
	CHAR* fileType = strrchr(filePath, '.');

	CHAR totalFilePath[MAX_PATH];
	sprintf_s(totalFilePath, MAX_PATH, "%s\\%s", gExeFilePath, filePath);

	if (strcmp(fileType, ".tga") == 0)
	{
		texture = loadTGA(totalFilePath);
	}

	// auswerten ob die Textur geladen werden konnte
	return (texture != NULL);
}

CTexture* CImageLoader::loadTGA(CHAR *filepath)
{
	T_TGA_HEADER header;
	
	ifstream file(filepath, std::ios_base::binary);

	if (file.is_open() == FALSE)
		return NULL;

	if (file.read((char*)&header, sizeof(T_TGA_HEADER)) == FALSE)
	{
		file.close();
		return NULL;
	}

	if (header.imageType != 2)
	{
		file.close();
		return NULL;
	}

	GLuint width = header.imageWidth;
	GLuint height = header.imageHeight;
	GLuint bpp = header.pixelDepth;
	GLuint type = GL_RGBA;

	if ((width <= 0) || (height <= 0) || ((bpp != 24) && (bpp != 32)))
		return NULL;

	if (bpp == 24)
		type = GL_RGB;

	GLuint bytesPerPixel = bpp /8;
	GLuint imagesize = width * height* bytesPerPixel;

	GLubyte* imageData = new UCHAR[imagesize];

	if (imageData == 0)
		return NULL;

	if (file.read( (char*)imageData, imagesize ) == FALSE)
	{
		delete [] imageData;
		return NULL;
	}

	// file schließen
	file.close();

	char out[100];

	// BGR -> RGB
	for (GLuint i = 0; i < (GLuint)imagesize; i += bytesPerPixel)
	{
		GLuint temp = imageData[i];
		imageData[i] = imageData[i +2];
		imageData[i +2] = temp;
	}

	return new CTexture(imageData, width, height, bpp, type);
}