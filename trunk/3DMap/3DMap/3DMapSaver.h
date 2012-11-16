#ifndef _3D_MAP_SAVER
#define _3D_MAP_SAVER

#include "3DMapFormat.h"
#include "zlib.h"

class C3DMapSaver
{
public:
	C3DMapSaver();

	BOOLEAN saveMap(C3DMap* map, char* filename);

protected:
	
};

#endif