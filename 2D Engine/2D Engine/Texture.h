#ifndef TEXTURE_H
#define TEXTURE_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "gl/gl.h"
#include "gl/glu.h"

class CTexture
{
public:
	CTexture(GLubyte* imageData, GLuint width, GLuint height, GLuint bitPerPixel, GLuint type);
	~CTexture();

	GLuint getTexID();
	VOID addReference();
	VOID removeReference();
	ULONG getReferenceCount();

	GLuint getWidth();
	GLuint getHeight();

protected:
	ULONG	mReferenceCount;
	GLubyte* mImageData;
	GLuint	mWidth;
	GLuint	mHeight;
	GLuint	mBitPerPixel;
	GLuint	mType;
	GLuint	mTexID;	// OpenGL Tex ID	
};

#endif