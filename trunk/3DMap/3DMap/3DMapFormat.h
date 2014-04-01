#ifndef _3D_MAP_FORMAT
#define _3D_MAP_FORMAT

#include "3DMapData.h"

const CHAR DEFAULT_IDENT[4] = {'_', 'm', 'f', 'f'};
const ULONG MAP_3D_VERSION = 0x01000000;

typedef struct MAP_3D_FILEHEADER
{
	CHAR ident[4];
	ULONG version;

//	BOOLEAN bFloatingPoint;
//	UCHAR byteCount;

	ULONG pointCountX;
	ULONG pointCountY;
} T_MAP_3D_FILEHEADER;

#endif