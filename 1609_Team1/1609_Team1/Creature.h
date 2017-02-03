#pragma once
#include "ObjectManager.h"
class Creature :
	public Object
{
public:
	Creature();
	~Creature();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);
};

