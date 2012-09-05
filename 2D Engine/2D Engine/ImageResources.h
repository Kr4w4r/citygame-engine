#ifndef IMAGE_RESOURCES_H
#define IMAGE_RESOURCES_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

typedef enum IMAGE_ID
{
	IMAGE_TEST,
	IMAGE_GRASS_TILE,
	IMAGE_TREE_TILE,
	IMAGE_MAN_STAND,
	IMAGE_COLOR_TEST,

	// Spieler Lauf Animation
	IMAGE_PLAYER_RUN_1_RIGHT,
	IMAGE_PLAYER_RUN_2_RIGHT,
	IMAGE_PLAYER_RUN_3_RIGHT,
	IMAGE_PLAYER_RUN_4_RIGHT,
	IMAGE_PLAYER_RUN_1_LEFT,
	IMAGE_PLAYER_RUN_2_LEFT,
	IMAGE_PLAYER_RUN_3_LEFT,
	IMAGE_PLAYER_RUN_4_LEFT,
} E_IMAGE_ID;

typedef struct S_IMAGE_RESOURCE
{
	IMAGE_ID imageId;
	CHAR filePath[MAX_PATH];
} T_IMAGE_RESOURCE;

const T_IMAGE_RESOURCE gImageResources[] = 
{
	{IMAGE_TEST, "image.tga"},
	{IMAGE_GRASS_TILE, "MapTiles/grass_128.tga"},
	{IMAGE_TREE_TILE, "MapTiles/tree_128.tga"},
	{IMAGE_MAN_STAND, "PlayerSprite/stand.tga"},
	{IMAGE_COLOR_TEST, "test.tga"},

	// Spieler Lauf Animation
	{IMAGE_PLAYER_RUN_1_RIGHT, "PlayerSprite/run1.tga"},
	{IMAGE_PLAYER_RUN_2_RIGHT, "PlayerSprite/run2.tga"},
	{IMAGE_PLAYER_RUN_3_RIGHT, "PlayerSprite/run3.tga"},
	{IMAGE_PLAYER_RUN_4_RIGHT, "PlayerSprite/run4.tga"},
	{IMAGE_PLAYER_RUN_1_LEFT, "PlayerSprite/run1left.tga"},
	{IMAGE_PLAYER_RUN_2_LEFT, "PlayerSprite/run2left.tga"},
	{IMAGE_PLAYER_RUN_3_LEFT, "PlayerSprite/run3left.tga"},
	{IMAGE_PLAYER_RUN_4_LEFT, "PlayerSprite/run4left.tga"},

};

#endif