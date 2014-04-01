#include "3DMapLevelOfDetailRenderer.h"

C3DMapLevelOfDetailRenderer::C3DMapLevelOfDetailRenderer(IMap* pMap, UCHAR maxSegmentDepth)
:mpMap(pMap)
{
	if (maxSegmentDepth > 16) maxSegmentDepth = 16;

	mpRootSegment = NULL;
	createMapSegments(maxSegmentDepth);

	ULONG segmentSize = mpMap->getWidth();
	ULONG gridSize = (ULONG)pow(2, maxSegmentDepth);
	if (segmentSize < gridSize) gridSize = segmentSize;

	GLfloat worldMapWidthHalf = (mpMap->getMapCorner(segmentSize, 0)->x - mpMap->getMapCorner(0, 0)->x);
	worldMapWidthHalf /= 2;
	while (gridSize >= 1)
	{
		DETAIL_LEVEL_THRESHOLD threshold;
		threshold.first = gridSize;
		threshold.second = worldMapWidthHalf * 0.75;

		mLevelThresholds.insert(threshold);

		gridSize /= 2;
		worldMapWidthHalf /= 2;
	}
}

C3DMapLevelOfDetailRenderer::~C3DMapLevelOfDetailRenderer()
{
	// Map Segemente wieder Freigeben
	if (mpRootSegment != NULL)
	{
		deleteMapSegment(mpRootSegment);
	}
}

void renderSegment(IMap* pMap, CMapSegment* pSegment)
{
	if (pSegment->isDetailLevelUsed() == false)
	{
		pSegment->render(pMap);
		return;
	}

	if (pSegment->mUpperLeftSegment != NULL)
	{
		if (pSegment->mUpperLeftSegment->isDetailLevelUsed() == false)
		{
			pSegment->mUpperLeftSegment->render(pMap);
		}
		else
		{
			renderSegment(pMap, pSegment->mUpperLeftSegment);
		}
	}
	
	if (pSegment->mLowerLeftSegment != NULL)
	{
		if (pSegment->mLowerLeftSegment->isDetailLevelUsed() == false)
		{
			pSegment->mLowerLeftSegment->render(pMap);
		}
		else
		{
			renderSegment(pMap, pSegment->mLowerLeftSegment);
		}
	}

	if (pSegment->mUpperRightSegment != NULL)
	{
		if (pSegment->mUpperRightSegment->isDetailLevelUsed() == false)
		{
			pSegment->mUpperRightSegment->render(pMap);
		}
		else
		{
			renderSegment(pMap, pSegment->mUpperRightSegment);
		}
	}

	if (pSegment->mLowerRightSegment != NULL)
	{
		if (pSegment->mLowerRightSegment->isDetailLevelUsed() == false)
		{
			pSegment->mLowerRightSegment->render(pMap);
		}
		else
		{
			renderSegment(pMap, pSegment->mLowerRightSegment);
		}
	}

	// Wenn keine Kindsemente vorhanden sind muss dieses Segment selbst gerendert werden
	if (pSegment->mUpperLeftSegment == NULL && 
		pSegment->mLowerLeftSegment == NULL && 
		pSegment->mUpperRightSegment == NULL && 
		pSegment->mLowerRightSegment == NULL)
	{
		pSegment->render(pMap);
	}
}

void C3DMapLevelOfDetailRenderer::render(CVector3f cameraPosition)
{
	if (recalculateMapSegments(cameraPosition) == true)
	{
		renderSegment(mpMap, mpRootSegment);
	}
}

void C3DMapLevelOfDetailRenderer::deleteMapSegment(CMapSegment* pSegment)
{
	if (pSegment->mLowerLeftSegment != NULL)	deleteMapSegment(pSegment->mLowerLeftSegment);
	if (pSegment->mLowerRightSegment != NULL)	deleteMapSegment(pSegment->mLowerRightSegment);
	if (pSegment->mUpperLeftSegment != NULL)	deleteMapSegment(pSegment->mUpperLeftSegment);
	if (pSegment->mUpperRightSegment != NULL)	deleteMapSegment(pSegment->mUpperRightSegment);

	delete pSegment;
}

void C3DMapLevelOfDetailRenderer::createMapSegments(UCHAR maxSegmentDepth)
{
	

	ULONG maxGridSize = (ULONG)pow(2, maxSegmentDepth);

	// Es werden derzeit nur Quadratische Maps unterstützt
	ULONG segmentSize = mpMap->getHeight();
	ULONG gridSize = segmentSize;
	//ULONG segmentWidth = mpMap->getWidth();
	//ULONG segmentHeight = mpMap->getHeight();

	if (maxGridSize < gridSize)	gridSize = maxGridSize;

	mpRootSegment = new CMapSegment(gridSize, segmentSize,
		0, 0, // Upper Left
		0, segmentSize, // Lower Left
		segmentSize, 0,  // Upper Right
		segmentSize, segmentSize); // Lower Right

	createMapSegmentChilds(mpRootSegment, maxSegmentDepth);
}

void C3DMapLevelOfDetailRenderer::createMapSegmentChilds(CMapSegment* pParent, UCHAR maxSegmentDepth)
{
	ULONG maxGridSize = (ULONG)pow(2, maxSegmentDepth);
	int childSegmentSize = pParent->getSegmentSize() / 2;
	ULONG childGridSize = childSegmentSize;

	if (maxGridSize < childGridSize)	childGridSize = maxGridSize;

	if ((maxSegmentDepth > 0) && (childSegmentSize >= 1))
	{
		/*
		Parent				Parent Segmented

		upper		upper
		left		right
		+-----------+		+-----+-----+
		|           |		|     |     |
		|           |		|     |     |
		|           |	=>	+-----+-----+
		|           |		|     |     |
		|           |		|     |     |
		+-----------+		+-----+-----+
		lower		lower
		left		right
		*/

		// Linkes oberes Segment erstellen
		MAP_SEGMENT_CORNER upperLeftBase = pParent->getUpperLeftCorner();
		pParent->mUpperLeftSegment = new CMapSegment(childGridSize, childSegmentSize, upperLeftBase);
		createMapSegmentChilds(pParent->mUpperLeftSegment, maxSegmentDepth - 1);

		// Linktes unteres Segment erstellen
		MAP_SEGMENT_CORNER lowerLeftBase = pParent->getUpperLeftCorner();
		lowerLeftBase.y += childSegmentSize;
		pParent->mLowerLeftSegment = new CMapSegment(childGridSize, childSegmentSize, lowerLeftBase);
		createMapSegmentChilds(pParent->mLowerLeftSegment, maxSegmentDepth - 1);

		// Rechtes oberes Segment erstellen
		MAP_SEGMENT_CORNER upperRightBase = pParent->getUpperLeftCorner();
		upperRightBase.x += childSegmentSize;
		pParent->mUpperRightSegment = new CMapSegment(childGridSize, childSegmentSize, upperRightBase);
		createMapSegmentChilds(pParent->mUpperRightSegment, maxSegmentDepth - 1);

		// Rechtes unteres Segement erstellen
		MAP_SEGMENT_CORNER lowerRightBase = pParent->getUpperLeftCorner();
		lowerRightBase.x += childSegmentSize;
		lowerRightBase.y += childSegmentSize;
		pParent->mLowerRightSegment = new CMapSegment(childGridSize, childSegmentSize, lowerRightBase);
		createMapSegmentChilds(pParent->mLowerRightSegment, maxSegmentDepth - 1);
	}
}

bool C3DMapLevelOfDetailRenderer::recalculateMapSegments(CVector3f cameraPosition)
{


	recalculateMapSegment(mpRootSegment, cameraPosition);
	return true;
}

bool C3DMapLevelOfDetailRenderer::recalculateMapSegment(CMapSegment* pSegment, CVector3f cameraPosition)
{
	if (isInsideSegment(cameraPosition, pSegment) == true)
	{
		pSegment->setDetailLevelUsed(true);
		if (pSegment->mUpperLeftSegment != NULL)	recalculateMapSegment(pSegment->mUpperLeftSegment, cameraPosition);
		if (pSegment->mLowerLeftSegment != NULL)	recalculateMapSegment(pSegment->mLowerLeftSegment, cameraPosition);
		if (pSegment->mUpperRightSegment != NULL)	recalculateMapSegment(pSegment->mUpperRightSegment, cameraPosition);
		if (pSegment->mLowerRightSegment != NULL)	recalculateMapSegment(pSegment->mLowerRightSegment, cameraPosition);
	}
	else
	{
		if (getDistance(cameraPosition, pSegment) < mLevelThresholds.find(pSegment->getGridSize())->second)
		{
			pSegment->setDetailLevelUsed(true);
			if (pSegment->mUpperLeftSegment != NULL)	recalculateMapSegment(pSegment->mUpperLeftSegment, cameraPosition);
			if (pSegment->mLowerLeftSegment != NULL)	recalculateMapSegment(pSegment->mLowerLeftSegment, cameraPosition);
			if (pSegment->mUpperRightSegment != NULL)	recalculateMapSegment(pSegment->mUpperRightSegment, cameraPosition);
			if (pSegment->mLowerRightSegment != NULL)	recalculateMapSegment(pSegment->mLowerRightSegment, cameraPosition);
		}
		else
		{
			pSegment->setDetailLevelUsed(false);
		}
	}

	return false;
}

bool C3DMapLevelOfDetailRenderer::isInsideSegment(CVector3f cameraPosition, CMapSegment* pSegment)
{
	// Welt-Koordinaten des Segmentes bestimmen
	MAP_CORNER* upperLeft = mpMap->getMapCorner(pSegment->getUpperLeftCorner().x, pSegment->getUpperLeftCorner().y);
	MAP_CORNER* lowerRight = mpMap->getMapCorner(pSegment->getLowerRightCorner().x, pSegment->getLowerRightCorner().y);

	if ((upperLeft->x <= cameraPosition.x) && (cameraPosition.x <= lowerRight->x))
	{
		if ((lowerRight->y <= cameraPosition.y) && (cameraPosition.y <= upperLeft->y))
		{
			return true;
		}
	}
	return false;
}

GLfloat C3DMapLevelOfDetailRenderer::getDistance(CVector3f cameraPosition, CMapSegment* pSegment)
{
	MAP_CORNER upperLeft = *mpMap->getMapCorner(pSegment->getUpperLeftCorner().x, pSegment->getUpperLeftCorner().y);
	MAP_CORNER lowerLeft = *mpMap->getMapCorner(pSegment->getLowerLeftCorner().x, pSegment->getLowerLeftCorner().y);
	MAP_CORNER upperRight = *mpMap->getMapCorner(pSegment->getUpperRightCorner().x, pSegment->getUpperRightCorner().y);
	MAP_CORNER lowerRight = *mpMap->getMapCorner(pSegment->getLowerRightCorner().x, pSegment->getLowerRightCorner().y);

	upperLeft.z = 0;
	lowerLeft.z = 0;
	upperRight.z = 0;
	upperLeft.z = 0;
	cameraPosition.z = 0;

	CVector3f toUpperLeft = cameraPosition - upperLeft;
	CVector3f toLowerLeft = cameraPosition - lowerLeft;
	CVector3f toUpperRight = cameraPosition - upperRight;
	CVector3f toLowerRight = cameraPosition - lowerRight;

	GLfloat distance = toUpperLeft.length();
	if (toLowerLeft.length() < distance)	distance = toLowerLeft.length();
	if (toUpperRight.length() < distance)	distance = toUpperRight.length();
	if (toLowerRight.length() < distance)	distance = toLowerRight.length();

	return distance;
}