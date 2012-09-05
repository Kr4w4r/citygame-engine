#include "TexturedElement.h"

CTexturedElement::CTexturedElement(E_RENDERLEVEL renderlevel, CTexture* texture)
: CElement2D(renderlevel)
{
	mTexture = 0;
	setTexture(texture);
}

CTexturedElement::CTexturedElement(float posX, float posY, float width, float height, E_RENDERLEVEL renderlevel, CTexture* texture)
: CElement2D(posX, posY, width, height, renderlevel)
{
	mTexture = 0;
	setTexture(texture);
}

CTexturedElement::CTexturedElement(CVector2f pos, CVector2f dimension, E_RENDERLEVEL renderlevel, CTexture* texture)
: CElement2D(pos, dimension, renderlevel)
{
	mTexture = 0;
	setTexture(texture);
}

CTexturedElement::~CTexturedElement()
{
	if (mTexture != NULL)
	{
		mTexture->removeReference();
		
		CHAR out[100];
		sprintf_s(out, 100, "[CTexturedElement::~CTexturedElement] -> removeReference() -> TexID: %u\n", mTexture->getTexID());
		OutputDebugStringA(out);
	}
}

VOID CTexturedElement::setTexture(CTexture *texture)
{
	// alte Texturreferenz entfernen
	if (mTexture != NULL)
	{
		mTexture->removeReference();

		CHAR out[100];
		sprintf_s(out, 100, "[CTexturedElement::setTexture] -> removeReference() -> TexID: %u\n", mTexture->getTexID());
		OutputDebugStringA(out);
	}

	mTexture = texture;

	if (mTexture != NULL)
	{
		mTexture->addReference();

		CHAR out[100];
		sprintf_s(out, 100, "[CTexturedElement::setTexture] -> addReference() -> TexID: %u\n", mTexture->getTexID());
		OutputDebugStringA(out);
	}
}

CTexture* CTexturedElement::getTexture()
{
	return mTexture;
}

VOID CTexturedElement::render()
{
	glPushMatrix();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mTexture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTexture->getTexID());
	}else
	{
		glDisable(GL_TEXTURE_2D);
	}

	glTranslatef(mPos.x, mPos.y, (GLfloat)-mRenderlevel);
	glRotatef(mfAngle, 0,0,1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0,0);	glVertex3f(- (mDimension.x /2), - (mDimension.y /2), 0);
		glTexCoord2f(1,0);	glVertex3f(+ (mDimension.x /2), - (mDimension.y /2), 0);
		glTexCoord2f(1,1);	glVertex3f(+ (mDimension.x /2), + (mDimension.y /2), 0);
		glTexCoord2f(0,1);	glVertex3f(- (mDimension.x /2), + (mDimension.y /2), 0);
	glEnd();

	glPopMatrix();
}