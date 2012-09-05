#include "Texture.h"
#include <stdio.h> 

CTexture::CTexture(GLubyte* imageData, GLuint width, GLuint height, GLuint bitPerPixel, GLuint type)
{
	mReferenceCount = 0;

	mImageData = imageData;
	mWidth = width;
	mHeight = height;
	mBitPerPixel = bitPerPixel;
	mType = type;

	if (imageData != NULL)
	{
		// Textur bei OpenGL registrieren
		glGenTextures(1, &mTexID);
		glBindTexture(GL_TEXTURE_2D, mTexID);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, mType, mWidth, mHeight, 0, mType, GL_UNSIGNED_BYTE, mImageData);
	}
}

CTexture::~CTexture()
{
	if (mImageData != 0)
	{
		// Namen deregistrieren
		glDeleteTextures(1, &mTexID);
		delete []mImageData;
	}
}

GLuint CTexture::getTexID()
{
	return mTexID;
}

void CTexture::addReference()
{
	mReferenceCount++;
}

void CTexture::removeReference()
{
	if (mReferenceCount == 0)
	{
		char output[200];
		sprintf_s(output, sizeof(output), "CTexture::removeReference() -> removing invalid, referenceCount get below 0 <- TexID : %u\n", mTexID);
		OutputDebugString(output);
	}

	if (mReferenceCount != 0)
	{
		mReferenceCount--;
	}
}

ULONG CTexture::getReferenceCount()
{
	return mReferenceCount;
}

GLuint CTexture::getWidth()
{
	return mWidth;
}

GLuint CTexture::getHeight()
{
	return mHeight;
}

