#include "TextureAnimation.h"



CTextureAnimation::CTextureAnimation(GLuint animationStepTime)
{
	mAnimationStepTime = animationStepTime;
	mCurrentStep = 0;
	mLastUpdate = 0;
}

CTextureAnimation::~CTextureAnimation()
{
	for (T_ANIMATION_LIST_ITER iter = mAnimationList.begin(); iter != mAnimationList.end(); iter++)
	{
		(*iter)->removeReference();

		CHAR out[100];
		sprintf_s(out, 100, "[CTextureAnimation::~CTextureAnimation] -> removeReference() -> TexID: %u\n", (*iter)->getTexID());
		OutputDebugStringA(out);
	}
}

GLvoid CTextureAnimation::addAnimationStep(CTexture *texture)
{
	mAnimationList.push_back(texture);
	texture->addReference();
	CHAR out[100];
	sprintf_s(out, 100, "[CTextureAnimation::addAnimationStep] -> addReference() -> TexID: %u\n", texture->getTexID());
	OutputDebugStringA(out);
}

GLvoid CTextureAnimation::resetAnimation()
{
	mCurrentStep = 0;
	mLastUpdate = 0;
}

bool CTextureAnimation::checkUpdate()
{
	if ((mLastUpdate + mAnimationStepTime) < GetTickCount())
	{
		return true;
	}
	return false;
}

bool CTextureAnimation::getNextAnimationStep(CTexture* &texture)
{
	// nächstes Bild setzen
	if ((mCurrentStep +1) >= mAnimationList.size())
	{
		mCurrentStep = 0;
	}else
	{
		mCurrentStep++;
	}

	// Bild holen
	texture = mAnimationList.at(mCurrentStep);

	mLastUpdate = GetTickCount();
	return true;
}

GLuint CTextureAnimation::getTotalAnimationTime()
{
	// zeit * bilder;
	return mAnimationStepTime * mAnimationList.size();
}
