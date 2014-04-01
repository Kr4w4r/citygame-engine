#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "MapSegment.h"

CMapSegment::CMapSegment(int gridSize, int segmentSize,
	int xUpperLeft, int yUpperLeft,
	int xLowerLeft, int yLowerLeft,
	int xUpperRight, int yUpperRight,
	int xLowerRight, int yLowerRight)
{
	mGridSize = gridSize;
	mSegmentSize = segmentSize;

	mUpperLeftCorner.x = xUpperLeft;
	mUpperLeftCorner.y = yUpperLeft;

	mLowerLeftCorner.x = xLowerLeft;
	mLowerLeftCorner.y = yLowerLeft;

	mUpperRightCorner.x = xUpperRight;
	mUpperRightCorner.y = yUpperRight;

	mLowerRightCorner.x = xLowerRight;
	mLowerRightCorner.y = yLowerRight;

	mUpperLeftSegment = NULL;
	mLowerLeftSegment = NULL;
	mUpperRightSegment = NULL;
	mLowerRightSegment = NULL;

	mbDetailLevelUsed = false;
}

CMapSegment::CMapSegment(int gridSize, int segmentSize, MAP_SEGMENT_CORNER upperLeftCorner)
{
	mGridSize = gridSize;
	mSegmentSize = segmentSize;

	mUpperLeftCorner = upperLeftCorner;

	mLowerLeftCorner.x = mUpperLeftCorner.x;
	mLowerLeftCorner.y = mUpperLeftCorner.y + segmentSize;

	mUpperRightCorner.x = mUpperLeftCorner.x + segmentSize;
	mUpperRightCorner.y = mUpperLeftCorner.y;

	mLowerRightCorner.x = mUpperLeftCorner.x + segmentSize;
	mLowerRightCorner.y = mUpperLeftCorner.y + segmentSize;

	mUpperLeftSegment = NULL;
	mLowerLeftSegment = NULL;
	mUpperRightSegment = NULL;
	mLowerRightSegment = NULL;

	mbDetailLevelUsed = false;
}

CMapSegment::~CMapSegment()
{}

void CMapSegment::render(IMap* pMap)
{
	glPushMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLfloat maxHeight = pMap->getMaxHeight();

	CVector3f color;
	for (GLint y = mUpperLeftCorner.y; y < mLowerRightCorner.y; y += getGridSize())
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (GLint x = mUpperLeftCorner.x; x <= mLowerRightCorner.x; x += getGridSize())
		{
			MAP_CORNER* point = pMap->getMapCorner(x, y);
			color = getColor(point->z, maxHeight);
			glColor3f(color.x, color.y, color.z);
			glVertex3f(point->x, point->y, point->z);

			MAP_CORNER* nextPoint = pMap->getMapCorner(x, y + getGridSize());
			color = getColor(nextPoint->z, maxHeight);
			glColor3f(color.x, color.y, color.z);
			glVertex3f(nextPoint->x, nextPoint->y, nextPoint->z);
		}
		glEnd();
	}

	glPopMatrix();
}

CVector3f CMapSegment::getColor(GLfloat height, GLfloat maxHeight)
{
	CVector3f color;
	/*
	if (height >= 0)
	{
	color.y = height / mMaxHeight;
	color.x = 1- height / mMaxHeight;
	}
	else
	{
	color.x = 1- height / mMaxHeight;
	color.z = -1 * height / mMaxHeight;
	}
	*/

	GLfloat colorCode = (height / maxHeight + 1);
	colorCode /= 2;

	if (colorCode < 0.1)
		int i = 0;

	if (colorCode > 0.9)
		int ji = 0;

	color.x = colorCode;
	color.y = colorCode;
	color.z = colorCode;

	return color;
}