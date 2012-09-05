#include "AnimatedSprite.h"

CAnimatedSprite::CAnimatedSprite(CTexture* texture)
:CCollisionSprite(texture)
{
	mDefaultTexture = texture;
	mCurrentAnimation = ANIM_NONE;
	
	// wir können hier noch nicht die Animation der Übergeordneten Klasse 
	// aufrufen da sie hier noch nicht konstruiert wurde
//	initAnimations();
}

CAnimatedSprite::CAnimatedSprite(float posX, float posY, float width, float height, CTexture *texture)
:CCollisionSprite(posX, posY, width, height, texture)
{
	mDefaultTexture = texture;
	mCurrentAnimation = ANIM_NONE;
	
	// wir können hier noch nicht die Animation der Übergeordneten Klasse 
	// aufrufen da sie hier noch nicht konstruiert wurde
//	initAnimations();
}

CAnimatedSprite::CAnimatedSprite(CVector2f pos, CVector2f dimension, CTexture *texture)
:CCollisionSprite(pos, dimension, texture)
{
	mDefaultTexture = texture;
	mCurrentAnimation = ANIM_NONE;

	// wir können hier noch nicht die Animation der Übergeordneten Klasse 
	// aufrufen da sie hier noch nicht konstruiert wurde
//	initAnimations();
}

CAnimatedSprite::~CAnimatedSprite()
{
	if (mAnimations.size() > 0)
	{
		// AnimationMap freigeben
		for (ANIMATION_MAP_ITER iter = mAnimations.begin(); iter != mAnimations.end(); iter++)
		{
			// TextureAnimation freigeben
			delete (*iter).second;
		}
	}

	mAnimations.clear();
}

void CAnimatedSprite::render()
{
	if (mCurrentAnimation != ANIM_NONE)
	{
		ANIMATION_MAP_ITER iter = mAnimations.find(mCurrentAnimation);

		if ((*iter).second->checkUpdate() == true)
		{
			(*iter).second->getNextAnimationStep(mTexture);
		}
	}else
	{
		mTexture = mDefaultTexture;
	}

	CCollisionSprite::render();

	// Boundingbox anzeigen
	mBoundingBox.render();
}

E_ANIMATION_TYPE CAnimatedSprite::getCurrentAnimation()
{
	return mCurrentAnimation;
}

GLboolean CAnimatedSprite::setCurrentAnimation(E_ANIMATION_TYPE animType)
{
	if (mCurrentAnimation != animType)
	{
		mCurrentAnimation = animType;

		// Animation zurücksetzen
		ANIMATION_MAP_ITER iter = mAnimations.find(mCurrentAnimation);

		if (iter != mAnimations.end())
		{
			(*iter).second->resetAnimation();
			return true;
		}else
		{
			mCurrentAnimation = ANIM_NONE;
		}
	}
	return false;
}

void CAnimatedSprite::initAnimations()
{
}