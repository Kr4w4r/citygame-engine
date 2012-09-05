#ifndef IRENDERABLE_H
#define IRENDERABLE_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

class IRenderable
{
public:
	virtual VOID render() = 0;
};

#endif