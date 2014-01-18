#ifndef RANDOM_FRACTAL_3DMAP_GENERATOR_H
#define RANDOM_FRACTAL_3DMAP_GENERATOR_H

#include "3DMap.h"

class CRandomFractal3DMapGenerator
{
public:
	CRandomFractal3DMapGenerator();
	~CRandomFractal3DMapGenerator();

	C3DMap* generateMap(GLint squareGridSize, GLfloat maxHeight);
	C3DMap* generateMap(GLint squareGridSize, GLfloat width, GLfloat height, GLfloat maxHeight);

protected:
	GLfloat getRandomHeight();

	void processSquares(GLint squareSize, GLfloat cellWidth, GLfloat cellHeight);
	void processDiamonds(GLint diamondSize, GLfloat cellWidth, GLfloat cellHeight);

	GLfloat getDiamondAverageHeight(GLint xCenter, GLint yCenter, GLint diamondSize);

	void flattenMap();
	void flattenSquare(int squareSize);
	GLfloat getAverageValueInRange(int steps);
	

	MAP_DATA mTempMap;
	GLint mTotalGridSize;

	GLfloat mXUpperLeft;
	GLfloat mYUpperLeft;

	GLfloat mMaxHeight;
	USHORT mIteration;
};

#endif
