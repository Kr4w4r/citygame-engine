#include "3DMapLoader.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
using namespace std;
using std::ifstream;

C3DMapLoader::C3DMapLoader()
{
}

BOOLEAN C3DMapLoader::loadMap(char* filename, C3DMapData*& pMap)
{
	ifstream fMapFile("test.mff", ios_base::binary);

	if ((fMapFile.is_open() != TRUE) || (fMapFile.bad() == TRUE))
	{
		OutputDebugString("Datei konnte nicht geöffnet werden\n");
		return FALSE;
	}


	fMapFile.seekg(0, ios_base::end);
	ULONG compressedBufferSize = (ULONG)fMapFile.tellg() - sizeof(ULONG);
	

	// Wieder auf den Anfang setzen
	fMapFile.seekg(0, ios_base::beg);

	// größe der Entpackten Daten ermitteln
	ULONG uncompressedBufferSize = 0;
	fMapFile.read((CHAR*)&uncompressedBufferSize, sizeof(ULONG));
	//uncompressedBufferSize *= 1.5;
	/*
	CHAR* pCompressedData = new CHAR[uncompressedBufferSize];//compressedBufferSize];
	CHAR* pUncompressedData = new CHAR[uncompressedBufferSize];
	memset(pCompressedData, 0x01, compressedBufferSize);
	memset(pUncompressedData, 0x02, uncompressedBufferSize);
	*/
	ULONG numCorners = (uncompressedBufferSize - sizeof(T_MAP_3D_FILEHEADER)) /12;
	
	T_MAP_3D_FILEHEADER fileHeader;
	fMapFile.read((CHAR*)&fileHeader, sizeof(T_MAP_3D_FILEHEADER));

	if (memcmp(fileHeader.ident, DEFAULT_IDENT, sizeof(DEFAULT_IDENT)) != 0)
	{
		OutputDebugString("Datei ist keine MFF-Datei\n");
		return FALSE;
	}

	MAP_DATA mapData = new MAP_CORNER**[fileHeader.pointCountX +1];
	for (int x = 0; x <= fileHeader.pointCountX; x++)
	{
		mapData[x] = new MAP_CORNER*[fileHeader.pointCountY +1];

		for (int y = 0; y <= fileHeader.pointCountY; y++)
		{
			mapData[x][y] = NULL;
		}
	}

	MAP_CORNER corner;
	for (int cornerIndex = 0; cornerIndex < numCorners; cornerIndex++)
	{
		fMapFile.read((CHAR*)&corner, sizeof(MAP_CORNER));

		if (fMapFile.eof() == TRUE)
		{
			OutputDebugString("EOF Error\n");
			return FALSE;
		}

		GLuint x = cornerIndex % fileHeader.pointCountX;
		GLuint y = cornerIndex / fileHeader.pointCountX;

		mapData[x][y] = new MAP_CORNER(corner.x, corner.y, corner.z);
	}

	fMapFile.close();

	pMap = new C3DMapData(fileHeader.pointCountX -1, fileHeader.pointCountY -1, mapData);

	return TRUE;
}