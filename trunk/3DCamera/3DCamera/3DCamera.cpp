#include "3DCamera.h"

C3DCamera::C3DCamera()
{}

C3DCamera::~C3DCamera()
{}

void C3DCamera::lookAt(CVector3f position)
{
	CVector3f xPlanePosition = CVector3f(0, mPosition.y, mPosition.z);
	CVector3f yPlanePosition = CVector3f(mPosition.x, 0, mPosition.z);
	
	/*float rotationX = xPlanePosition.angleToVector(CVector3f(0,0,-1));
	float rotationY = yPlanePosition.angleToVector(CVector3f(0,0,-1));
	*/
	float rotationX = mPosition.angleToVector(CVector3f(1,0,0));
	float rotationY = mPosition.angleToVector(CVector3f(0,1,0));

	if (mPosition.y > 0)
	{
		rotationX *= -1;
	}
	if (mPosition.x < 0)
	{
		rotationY *= -1;
	}

	mRotation.x = 90.f - rotationX;
	mRotation.y = 90.f - rotationY;
}

void C3DCamera::render()
{
	glPushMatrix();

	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glRotatef(mRotation.x, 1,0,0);
	glRotatef(mRotation.y, 0,1,0);
	glRotatef(mRotation.z, 0,0,1);
	
	
	glColor3f(0.f, 0.f, 1.f);

	glBegin(GL_POINTS);
		glVertex3f(0,0,0);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3f(-0.1,0,0);
		glVertex3f(+0.1,0,0);
		glVertex3f(0,0,0.5);
	glEnd();

	glPopMatrix();
}