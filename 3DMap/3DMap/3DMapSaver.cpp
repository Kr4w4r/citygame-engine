#include "3DMapSaver.h"
#include "stdio.h"
#include <fstream>
#include <iostream>
using namespace std;
using std::ofstream;

#include "windows.h"

C3DMapSaver::C3DMapSaver()
{}

BOOLEAN C3DMapSaver::saveMap(C3DMapData* map, char* filename)
{
	GLuint mapWidth = map->getWidth();
	GLuint mapHeight = map->getHeight();

	// Größe der Daten bestimmen
	ULONG fileSize = sizeof(MAP_3D_FILEHEADER);
	fileSize += sizeof(MAP_CORNER) * (mapWidth +1) * (mapHeight +1);

	// Daten in einem Speicher zusammenführen
	UCHAR* pMapData = new UCHAR[fileSize];
	memset(pMapData, 0, fileSize);

	MAP_3D_FILEHEADER* pMapFileHeader = (MAP_3D_FILEHEADER*)pMapData;

	memcpy(pMapFileHeader->ident, DEFAULT_IDENT, sizeof(DEFAULT_IDENT));
	pMapFileHeader->version = MAP_3D_VERSION;
	pMapFileHeader->pointCountX = mapWidth +1;
	pMapFileHeader->pointCountY = mapHeight +1;

	MAP_CORNER* pCorner = (MAP_CORNER*)((CHAR*)pMapFileHeader + sizeof(T_MAP_3D_FILEHEADER));

	for (ULONG y = 0; y < pMapFileHeader->pointCountY; y++)
	{
		for (ULONG x = 0; x < pMapFileHeader->pointCountX; x++)
		{
			MAP_CORNER* pMapCorner = map->getMapCorner(x, y);
			if (pMapCorner == NULL)
			{
				delete [] pMapData;
				return FALSE;
			}

			*pCorner = *pMapCorner;

			// Pointer weiterschieben
			pCorner++;
		}
	} 

	// Daten komprimieren

	//zlib states that the source buffer must be at least 0.1
	//times larger than the source buffer plus 12 bytes
	//to cope with the overhead of zlib data streams
	ULONG compressedFileBufferSize = fileSize + (ULONG)(fileSize * 0.1) + 12;
	UCHAR* pCompressionBuffer = new UCHAR[compressedFileBufferSize];

	//compress((Bytef*)pCompressionBuffer, &compressedFileBufferSize, (Bytef*)pMapData, fileSize);
	//compress2((Bytef*)pCompressionBuffer, &compressedFileBufferSize, (Bytef*)pMapData, fileSize, Z_BEST_COMPRESSION);	// Z_NO_COMPRESSION Z_BEST_SPEED Z_BEST_COMPRESSION Z_DEFAULT_COMPRESSION

	memcpy(pCompressionBuffer, pMapData, fileSize);
	compressedFileBufferSize = fileSize;

	// Die temporären Daten brauchen wir nicht mehr
	delete [] pMapData;
	/*
	MAP_3D_FILEHEADER* asd = (MAP_3D_FILEHEADER*)pCompressionBuffer;
	MAP_CORNER* test = (MAP_CORNER*)(asd +1);
	for (int i = 0; i < asd->pointCountX * asd->pointCountY; i++)
	{
		if (test->x > 1000)
			OutputDebugString("AHHHH");
		if (test->y > 1000)
			OutputDebugString("BHHHH");
		if (test->z > 1000)
			OutputDebugString("CHHHH");
		test++;
	}
	*/

	// Komprimierte Daten in die Datei schreiben
	/*
	FILE* fMapFile = fopen(filename, "w");
	fwrite(&fileSize, sizeof(ULONG), 1, fMapFile);
	fwrite(pCompressionBuffer, compressedFileBufferSize, 1, fMapFile);
	fclose(fMapFile);
	*/
	ofstream fMapFile("test.mff", ios_base::binary| ios_base::out);

	if ((fMapFile.is_open() == FALSE) || (fMapFile.bad() == TRUE))
	{
		OutputDebugString("Datei konnte nicht geöffnet werden");
		return FALSE;
	}

	fMapFile.write((CHAR*)&fileSize, sizeof(ULONG));
	fMapFile.write((CHAR*)pCompressionBuffer, compressedFileBufferSize);
	fMapFile.close();

	CHAR out[1024];
	sprintf_s(out, 1024, "Daten: %u Byte geschrieben: %u\n", fileSize, compressedFileBufferSize);
	OutputDebugString(out);

	delete [] pCompressionBuffer;
	return TRUE;
}