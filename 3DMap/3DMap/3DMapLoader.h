#ifndef _3D_MAP_LOADER
#define _3D_MAP_LOADER

#include "3DMapFormat.h"
#include "zlib.h"

class C3DMapLoader
{
public:
	C3DMapLoader();

	BOOLEAN test();
	BOOLEAN loadMap(char* filename, C3DMapData*& map);
};

#endif