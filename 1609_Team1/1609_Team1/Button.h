#pragma once
#include "RenderManager.h"
#include <list>

class Button
{
protected:
	list<Box*> m_boxList;

public:
	Button();
	~Button();
};

