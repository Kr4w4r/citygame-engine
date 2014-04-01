#pragma once

#include "IMap.h"

typedef struct
{
	int x;
	int y;
} MAP_SEGMENT_CORNER;

class CMapSegment
{
public:
	CMapSegment(int gridSize, int segmentSize,
		int xUpperLeft, int yUpperLeft,
		int xLowerLeft, int yLowerLeft,
		int xUpperRight, int yUpperRight,
		int xLowerRight, int yLowerRight);
	CMapSegment(int gridSize, int segmentSize, MAP_SEGMENT_CORNER upperLeftCorner);
	~CMapSegment();

	int getSegmentSize() { return mSegmentSize; };
	int getGridSize() { return mGridSize; };

	MAP_SEGMENT_CORNER getUpperLeftCorner() { return mUpperLeftCorner; };
	MAP_SEGMENT_CORNER getLowerLeftCorner() { return mLowerLeftCorner; };
	MAP_SEGMENT_CORNER getUpperRightCorner() { return mUpperRightCorner; };
	MAP_SEGMENT_CORNER getLowerRightCorner() { return mLowerRightCorner; };

	void setDetailLevelUsed(bool bDetailLevelUsed) { mbDetailLevelUsed = bDetailLevelUsed; };
	bool isDetailLevelUsed() { return mbDetailLevelUsed; };

	void render(IMap* pMap);

private:
	CVector3f getColor(GLfloat height, GLfloat maxHeight);

public:
	CMapSegment* mUpperLeftSegment;
	CMapSegment* mLowerLeftSegment;
	CMapSegment* mUpperRightSegment;
	CMapSegment* mLowerRightSegment;

private:
	int mGridSize;
	int mSegmentSize;
	bool mbDetailLevelUsed;

	MAP_SEGMENT_CORNER mUpperLeftCorner;
	MAP_SEGMENT_CORNER mLowerLeftCorner;
	MAP_SEGMENT_CORNER mUpperRightCorner;
	MAP_SEGMENT_CORNER mLowerRightCorner;
};