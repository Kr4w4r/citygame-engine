#pragma once

#include "IMap.h"
#include "MapSegment.h"
#include <map>
using std::map;

class C3DMapLevelOfDetailRenderer
{
public:
	C3DMapLevelOfDetailRenderer(IMap* map, UCHAR maxSegmentDepth = 255);
	~C3DMapLevelOfDetailRenderer();

	void render(CVector3f cameraPosition);

private:
	void deleteMapSegment(CMapSegment* pSegment);

protected:
	void createMapSegments(UCHAR maxSegmentDepth);
	void createMapSegmentChilds(CMapSegment* pParent, UCHAR maxSegmentDepth);
	bool recalculateMapSegments(CVector3f cameraPosition);
	bool recalculateMapSegment(CMapSegment* pSegment, CVector3f cameraPosition);

	bool isInsideSegment(CVector3f cameraPosition, CMapSegment* pSegment);
	GLfloat getDistance(CVector3f cameraPosition, CMapSegment* pSegment);

protected:
	IMap* mpMap;
	CMapSegment* mpRootSegment;
	
	typedef map<int, GLfloat> DETAIL_LEVEL_THRESHOLD_MAP;
	typedef std::pair<int, GLfloat> DETAIL_LEVEL_THRESHOLD;
	typedef DETAIL_LEVEL_THRESHOLD_MAP::iterator DETAIL_LEVEL_THRESHOLD_MAP_IT;

	DETAIL_LEVEL_THRESHOLD_MAP mLevelThresholds;
};