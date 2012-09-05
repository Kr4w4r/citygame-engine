#ifndef TEXTURE_ANIMATION_H
#define TEXTURE_ANIMATION_H

#include "Texture.h"

#include <vector>
using std::vector;

class CTextureAnimation
{
public:
	CTextureAnimation(GLuint animationStepTime);
	~CTextureAnimation();

	GLvoid addAnimationStep(CTexture* texture);
	GLvoid resetAnimation();
	bool checkUpdate();
	bool getNextAnimationStep(CTexture* &texture);
	GLuint getTotalAnimationTime();

protected:
	GLuint mAnimationStepTime;
	GLuint mCurrentStep;
	ULONG mLastUpdate;

	typedef vector<CTexture*> T_ANIMATION_LIST;
	typedef vector<CTexture*>::iterator T_ANIMATION_LIST_ITER;
	T_ANIMATION_LIST mAnimationList;
};

#endif