#ifndef MD2_LOADER_H
#define MD2_LOADER_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

typedef float T_VEC3[3];

/* MD2 header */
typedef struct MD2_HEADER
{
  int ident;                  /* magic number: "IDP2" */
  int version;                /* version: must be 8 */

  int skinwidth;              /* texture width */
  int skinheight;             /* texture height */

  int framesize;              /* size in bytes of a frame */

  int num_skins;              /* number of skins */
  int num_vertices;           /* number of vertices per frame */
  int num_st;                 /* number of texture coordinates */
  int num_tris;               /* number of triangles */
  int num_glcmds;             /* number of opengl commands */
  int num_frames;             /* number of frames */

  int offset_skins;           /* offset skin data */
  int offset_st;              /* offset texture coordinate data */
  int offset_tris;            /* offset triangle data */
  int offset_frames;          /* offset frame data */
  int offset_glcmds;          /* offset OpenGL command data */
  int offset_end;             /* offset end of file */
} T_MD2_HEADER;

/* Texture name */
typedef struct MD2_SKIN
{
  char name[64];              /* texture file name */
} T_MD2_SKIN;

typedef struct MD2_COMPRESSED_VERTEX
{
	UCHAR vertex[3];
	UCHAR normalIndex;
} T_MD2_COMPRESSED_VERTEX;

typedef struct MD2_FRAME
{
  T_VEC3 scale;               /* scale factor */
  T_VEC3 translate;           /* translation vector */
  char name[16];              /* frame name */
  struct T_MD2_COMPRESSED_VERTEX *verts; /* list of frame's vertices */
} T_MD2_FRAME;



class CMD2Loader
{
public:
	CMD2Loader();
	~CMD2Loader();

	bool loadMD2(char* filePath);

protected:
	T_MD2_SKIN* mSkins;
	T_VEC3* mVertices;
};

#endif