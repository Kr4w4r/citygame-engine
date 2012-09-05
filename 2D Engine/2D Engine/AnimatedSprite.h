#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "CollisionSprite.h"
#include "TextureAnimation.h"
#include "animationResource.h"
#include <map>
using std::map;

class CAnimatedSprite : public CCollisionSprite
{
public:
	CAnimatedSprite(CTexture* texture = NULL);
	CAnimatedSprite(float posX, float posY, float width, float height, CTexture *texture = NULL);
	CAnimatedSprite(CVector2f pos, CVector2f dimension, CTexture *texture = NULL);
	~CAnimatedSprite();

	E_ANIMATION_TYPE getCurrentAnimation();
	GLboolean setCurrentAnimation(E_ANIMATION_TYPE animType);

	virtual void render();

protected:
	virtual void initAnimations() = 0;

protected:
	E_ANIMATION_TYPE mCurrentAnimation;

	typedef map<E_ANIMATION_TYPE, CTextureAnimation*> ANIMATION_MAP;
	typedef ANIMATION_MAP::value_type ANIMATION_MAP_VALUE;
	typedef ANIMATION_MAP::iterator ANIMATION_MAP_ITER;
	ANIMATION_MAP mAnimations;

	// da die aktuell gesetze Textur durch die Animation überschrieben wird, 
	// speichern wir uns eine Standard Textur für den fall das für eine 
	// Animation keine Bilder zur verfügung stehen
	CTexture* mDefaultTexture;
};

#endif