#include "3DMapData.h"

C3DMapData::C3DMapData(GLuint horizontalCellCount, GLuint verticalCellCount, GLfloat maxHeight)
{
	mWidth = horizontalCellCount;
	mHeight = verticalCellCount;
	mMaxHeight = maxHeight;

	generateFlatMap(mWidth, mHeight, 1.0f, 1.0f);
}

C3DMapData::C3DMapData(GLuint horizontalCellCount, GLuint verticalCellCount, GLfloat width, GLfloat height, GLfloat maxHeight)
{
	mWidth = horizontalCellCount; 
	mHeight = verticalCellCount;
	mMaxHeight = maxHeight;

	generateFlatMap(mWidth, mHeight, width, height);
}

C3DMapData::C3DMapData(GLuint horizontalCellCount, GLuint verticalCellCount, MAP_DATA mapData)
{
	mWidth = horizontalCellCount;
	mHeight = verticalCellCount;
	mMapData = mapData;
	mMaxHeight = 0;

	for (int x = 0; x < horizontalCellCount; x++)
	{
		for (int y = 0; y < verticalCellCount; y++)
		{
			if (mMapData[x][y]->z > mMaxHeight)
			{
				mMaxHeight = mMapData[x][y]->z;
			}
		}
	}

}

C3DMapData::~C3DMapData()
{
	// Speicher für die Map wieder freigeben
	for (GLint x = 0; x <= mWidth; x++)
	{
		for (GLint y = 0; y <= mHeight; y++)
		{
			delete mMapData[x][y];
		}

		delete[] mMapData[x];
		mMapData[x] = NULL;
	}
	delete[] mMapData;
	mMapData = NULL;
}

void C3DMapData::generateFlatMap(GLuint horizontalCellCount, GLuint verticalCellCount, GLfloat width, GLfloat height)
{
	mWidth = horizontalCellCount;
	mHeight = verticalCellCount;

	GLfloat xUpperLeft = -width /2;
	GLfloat yUpperLeft = height /2;

	GLfloat cellWidth = width / horizontalCellCount;
	GLfloat cellHeight = height / verticalCellCount;

	// MapDaten initialisieren (2D Array mit MAP_CORNER* Elementen)
	// +1 weil: wenn man z.B. 4 Zellen hat braucht man auf einer Kante
	// 5 Ecken also immer + eine Ecke
	mMapData = new MAP_CORNER**[horizontalCellCount +1];
	for (GLuint yLoop = 0; yLoop <= horizontalCellCount; yLoop++)
	{
		mMapData[yLoop] = new MAP_CORNER*[verticalCellCount +1];
	}

	// Grid erzeugen
	for (GLuint y = 0; y <= verticalCellCount; y++)
	{
		for (GLuint x = 0; x <= horizontalCellCount; x++)
		{
			GLfloat xCoord = xUpperLeft + x * cellWidth;
			GLfloat yCoord = yUpperLeft - y * cellHeight;
			mMapData[x][y] = new MAP_CORNER(xCoord, yCoord, 0);
		}
	}
}

void C3DMapData::render()
{
	glPushMatrix();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	CVector3f color;
	for (GLint y = 0; y < mHeight; y++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (GLint x = 0; x <= mWidth; x++)
		{
			color = getColor(mMapData[x][y]->z);
			glColor3f(color.x, color.y, color.z);
			glVertex3f(mMapData[x][y]->x, mMapData[x][y]->y, mMapData[x][y]->z);

			color = getColor(mMapData[x][y+1]->z);
			glColor3f(color.x, color.y, color.z);
			glVertex3f(mMapData[x][y+1]->x, mMapData[x][y+1]->y, mMapData[x][y+1]->z);
		}
		glEnd();
	}
	
	glPopMatrix();
}

CVector3f C3DMapData::getColor(GLfloat height)
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

	GLfloat colorCode = (height / mMaxHeight +1) ;
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

MAP_CORNER* C3DMapData::getMapCorner(GLuint x, GLuint y)
{
	if ((x >= 0) && (x <= mWidth) && (y >= 0) && (y <= mHeight))
	{
		return mMapData[x][y];
	}
	return NULL;
}

GLuint C3DMapData::getWidth()
{
	return mWidth;
}

GLuint C3DMapData::getHeight()
{
	return mHeight;
}