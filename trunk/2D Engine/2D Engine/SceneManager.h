#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
using std::map;

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

protected:
	typedef map<ULONG, IRenderable*> RENDERABLE_MAP;
	typedef RENDERABLE_MAP::value_type RENDERABLE_MAP_TYPE;
	typedef RENDERABLE_MAP::iterator RENDERABLE_MAP_ITERATOR;

	RENDERABLE_MAP mMaps;
	RENDERABLE_MAP mSprites;
};

#endif