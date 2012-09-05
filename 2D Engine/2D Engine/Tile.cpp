#include "Tile.h"

CTile::CTile(float x, float y, float width, float height, CTexture* texture)
: CTexturedElement(x, y, width, height, RENDERLEVEL_MAP, texture)
{
	
}

CTile::~CTile()
{
}

void CTile::render()
{
	CTexturedElement::render();
	/*glPushMatrix();

	glTranslatef(mPos.x, mPos.y, (GLfloat)-mRenderlevel);
	
	if (mTexture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTexture->getTexID());
	}else
	{
		glDisable(GL_TEXTURE_2D);
	}

	glColor3f(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0,0);	glVertex3f(mPos.x - (mDimension.x /2), mPos.y - (mDimension.y /2), 0);
		glTexCoord2f(1,0);	glVertex3f(mPos.x + (mDimension.x /2), mPos.y - (mDimension.y /2), 0);
		glTexCoord2f(1,1);	glVertex3f(mPos.x + (mDimension.x /2), mPos.y + (mDimension.y /2), 0);
		glTexCoord2f(0,1);	glVertex3f(mPos.x - (mDimension.x /2), mPos.y + (mDimension.y /2), 0);
	glEnd();

	glPopMatrix();*/
}