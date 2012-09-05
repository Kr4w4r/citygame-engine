#include "PlayerSprite.h"
#include "TextureAnimation.h"
#include "ImageManager.h"

#include "mathMacros.h"

CPlayerSprite::CPlayerSprite(CTexture* texture)
: CAnimatedSprite(texture)
{
	initAnimations();
}

CPlayerSprite::CPlayerSprite(float posX, float posY, float width, float height, CTexture *texture)
: CAnimatedSprite(posX, posY, width, height, texture)
{
	initAnimations();
}

CPlayerSprite::CPlayerSprite(CVector2f pos, CVector2f dimension, CTexture *texture)
: CAnimatedSprite(pos, dimension, texture)
{
	initAnimations();
}

CPlayerSprite::~CPlayerSprite()
{
}

void CPlayerSprite::initAnimations()
{
	CTexture* texture = NULL;
	CTextureAnimation* animation = NULL;

	// Animation: Laufen Rechts
	{
		animation = new CTextureAnimation(150);

		gImageManager.getImage(IMAGE_PLAYER_RUN_1_RIGHT, texture);
		animation->addAnimationStep(texture);
		gImageManager.getImage(IMAGE_PLAYER_RUN_2_RIGHT, texture);
		animation->addAnimationStep(texture);
		gImageManager.getImage(IMAGE_PLAYER_RUN_3_RIGHT, texture);
		animation->addAnimationStep(texture);
		gImageManager.getImage(IMAGE_PLAYER_RUN_4_RIGHT, texture);
		animation->addAnimationStep(texture);

		ANIMATION_MAP_VALUE value (ANIM_MOVE_RIGHT, animation);
		mAnimations.insert(value);
	}

	// Animation: Laufen Links
	{
		animation = new CTextureAnimation(150);

		gImageManager.getImage(IMAGE_PLAYER_RUN_1_LEFT, texture);
		animation->addAnimationStep(texture);
		gImageManager.getImage(IMAGE_PLAYER_RUN_2_LEFT, texture);
		animation->addAnimationStep(texture);
		gImageManager.getImage(IMAGE_PLAYER_RUN_3_LEFT, texture);
		animation->addAnimationStep(texture);
		gImageManager.getImage(IMAGE_PLAYER_RUN_4_LEFT, texture);
		animation->addAnimationStep(texture);

		ANIMATION_MAP_VALUE value (ANIM_MOVE_LEFT, animation);
		mAnimations.insert(value);
	}	
}

void CPlayerSprite::setRotation(float angle)
{
	CAnimatedSprite::setRotation(angle);

	// Richtungsvektor anpassen
	mDirection.x = cos(DEG(angle));
	mDirection.y = sin(DEG(angle));

	mDirection.normalize();

	char out[100];
	sprintf_s(out, 100, "New Direction: Angle: %.2f X: %.3f Y: %.3f\n", mfAngle, mDirection.x, mDirection.y);
	OutputDebugStringA(out);
}

void CPlayerSprite::moveForward(float distance)
{
	setPosition(mPos.x + distance * mDirection.x, mPos.y + distance * mDirection.y);
}