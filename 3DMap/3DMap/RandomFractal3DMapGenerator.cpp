#include "RandomFractal3DMapGenerator.h"
#include "stdlib.h"	// rand & srand
#include "stdio.h"

CRandomFractal3DMapGenerator::CRandomFractal3DMapGenerator()
{}

CRandomFractal3DMapGenerator::~CRandomFractal3DMapGenerator()
{}

C3DMap* CRandomFractal3DMapGenerator::generateMap(GLint mTotalGridSize, GLfloat maxHeight)
{
	return generateMap(mTotalGridSize, 1.0f, 1.0f, maxHeight);
}

C3DMap* CRandomFractal3DMapGenerator::generateMap(GLint squareGridSize, GLfloat width, GLfloat height, GLfloat maxHeight)
{
	mIteration = 0;
	mMaxHeight = maxHeight;

	mTotalGridSize = squareGridSize;

	// wir m�ssen eine ungerade anzahl an Punkten haben, damit ordentlich 
	// die Mitte bestimmt werden kann
	/*if (horizontalCellCount %2 == 0)	horizontalCellCount++;
	if (verticalCellCount %2 == 0)		verticalCellCount++;*/

	// MapDaten initialisieren (2D Array mit MAP_CORNER* Elementen)
	// +1 weil: wenn man z.B. 4 Zellen hat braucht man auf einer Kante
	// 5 Ecken also immer + eine Ecke
	mTempMap = new MAP_CORNER**[mTotalGridSize +1];
	for (GLint xLoop = 0; xLoop < mTotalGridSize +1; xLoop++)
	{
		mTempMap[xLoop] = new MAP_CORNER*[mTotalGridSize +1];
	}

	// Alle Pointer erstmal mit NULL f�llen
	for (GLint xLoop = 0; xLoop < mTotalGridSize +1; xLoop++)
	{
		for (GLint yLoop = 0; yLoop < mTotalGridSize +1; yLoop++)
		{
			mTempMap[xLoop][yLoop] = NULL;
		}
	}

	// damit wir nachher die Position der Map-Punkte richtig positionieren k�nnen
	// ermitteln wir erstmal die obere linke Ecke und die gr��e der einzelnen Zellen
	mXUpperLeft = -width /2;
	mYUpperLeft = height /2;

	GLfloat cellWidth = width / mTotalGridSize;
	GLfloat cellHeight = height / mTotalGridSize;

	srand(GetTickCount());

	// zu aller erst die 4 Ecken erstellen.. sie dienen uns als Basis
	// oben links
	mTempMap[0][0] = new MAP_CORNER(mXUpperLeft, mYUpperLeft, mMaxHeight/*getRandomHeight()*/);
	// oben rechts
	mTempMap[mTotalGridSize][0] = new MAP_CORNER(mXUpperLeft + mTotalGridSize * cellWidth, mYUpperLeft, -mMaxHeight/*getRandomHeight()*/);
	// unten links
	mTempMap[0][mTotalGridSize] = new MAP_CORNER(mXUpperLeft, mYUpperLeft - mTotalGridSize * cellHeight, getRandomHeight());
	// unten rechts
	mTempMap[mTotalGridSize][mTotalGridSize] = new MAP_CORNER(mXUpperLeft + mTotalGridSize * cellWidth, mYUpperLeft - mTotalGridSize * cellHeight, getRandomHeight());

	processSquares(mTotalGridSize, cellWidth, cellHeight);

	for (GLint x = 0; x <= mTotalGridSize; x++)
	{
		for (GLint y = 0; y <= mTotalGridSize; y++)
		{
			if (mTempMap[x][y] == NULL)
			{
				CHAR out[100];
				sprintf(out, "Fehler bei [%u][%u]\n", x, y);
				OutputDebugString(out);
			}
		}
	}

	return new C3DMap(squareGridSize, squareGridSize, mTempMap);
}

GLfloat CRandomFractal3DMapGenerator::getRandomHeight()
{
	
	GLfloat ret = 2 * ((GLfloat)rand() / RAND_MAX) -1;
	ret /= pow(2.0, mIteration);
	ret *= mMaxHeight;

	return ret;
}

void CRandomFractal3DMapGenerator::processSquares(GLint squareSize, GLfloat cellWidth, GLfloat cellHeight)
{
	if (squareSize == 1)	return;

	for (GLint x = 0; x < mTotalGridSize; x += squareSize)
	{
		for (GLint y = 0; y < mTotalGridSize; y += squareSize)
		{
			// erstmal die durchschnittliche h�he des Punktes in der Mitte berechnen
			GLfloat averageHeight = 
				mTempMap[x][y]->z +							// oben links
				mTempMap[x][y + squareSize]->z +			// oben rechts
				mTempMap[x + squareSize][y]->z +			// unten links
				mTempMap[x + squareSize][y + squareSize]->z;// unten rechts

			averageHeight /= 4;

			// jetzt den Punkt erzeugen
			GLint xNewPointIndex = x + squareSize/2;
			GLint yNewPointIndex = y + squareSize/2;
			mTempMap[xNewPointIndex][yNewPointIndex] = new MAP_CORNER(mXUpperLeft + xNewPointIndex * cellWidth, mYUpperLeft - yNewPointIndex * cellHeight, averageHeight + getRandomHeight());
		}
	}

	processDiamonds(squareSize, cellWidth, cellHeight);
}

void CRandomFractal3DMapGenerator::processDiamonds(GLint diamondSize, GLfloat cellWidth, GLfloat cellHeight)
{
	mIteration++;

	GLint diamondMiddle = diamondSize /2;

	// wir haben 2 Durchg�nge
	// einmal wenn wir einen Offset auf der X-Achse haben
	for (GLint x = diamondMiddle; x <= mTotalGridSize; x += diamondSize)
	{
		for (GLint y = 0; y <= mTotalGridSize; y += diamondSize)
		{
			// wir haben jetzt also den Index der Mittelpunktes
			// jetzt m�ssen wir noch die Ecken suchen und die durchschnittsh�he berechnen
			GLfloat averageHeight = getDiamondAverageHeight(x, y, diamondSize);
			mTempMap[x][y] = new MAP_CORNER(mXUpperLeft + x * cellWidth, mYUpperLeft - y * cellHeight, averageHeight + getRandomHeight());
		}
	}

	// und einmal wenn wir einen Offset auf der Y-Achse haben
	for (GLint x = 0; x <= mTotalGridSize; x += diamondSize)
	{
		for (GLint y = diamondMiddle; y <= mTotalGridSize; y += diamondSize)
		{
			// wir haben jetzt also den Index der Mittelpunktes
			// jetzt m�ssen wir noch die Ecken suchen und die durchschnittsh�he berechnen
			GLfloat averageHeight = getDiamondAverageHeight(x, y, diamondSize);
			mTempMap[x][y] = new MAP_CORNER(mXUpperLeft + x * cellWidth, mYUpperLeft - y * cellHeight, averageHeight + getRandomHeight());
		}
	}

	processSquares(diamondMiddle, cellWidth, cellHeight);
}

GLfloat CRandomFractal3DMapGenerator::getDiamondAverageHeight(GLint xCenter, GLint yCenter, GLint diamondSize)
{
	GLint numCorners = 0;
	GLfloat averageHeight = 0;

	GLint halfDiamond = diamondSize /2;

	// wenn vorhanden, den Punkt LINKS ausw�hlen
	if ((xCenter - halfDiamond) >= 0)
	{
		averageHeight += mTempMap[xCenter - halfDiamond][yCenter]->z;
		numCorners++;
	}

	// wenn vorhanden, den Punkt RECHTS ausw�hlen
	if ((xCenter + halfDiamond) <= mTotalGridSize)
	{
		averageHeight += mTempMap[xCenter + halfDiamond][yCenter]->z;
		numCorners++;
	}

	// wenn vorhanden, den Punkt OBEN ausw�hlen
	if ((yCenter - halfDiamond) >= 0)
	{
		averageHeight += mTempMap[xCenter][yCenter - halfDiamond]->z;
		numCorners++;
	}

	// wenn vorhanden, den Punkt UNTEN ausw�hlen
	if ((yCenter + halfDiamond) <= mTotalGridSize)
	{
		averageHeight += mTempMap[xCenter][yCenter + halfDiamond]->z;
		numCorners++;
	}

	return averageHeight / numCorners;
}

void CRandomFractal3DMapGenerator::flattenMap()
{
	flattenSquare(mTotalGridSize);
}

void CRandomFractal3DMapGenerator::flattenSquare(GLint squareSize)
{

}

GLfloat CRandomFractal3DMapGenerator::getAverageValueInRange(int range)
{
	return 0;
}