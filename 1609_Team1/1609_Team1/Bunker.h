#pragma once
#include "ObjectManager.h"
class Bunker :
	public Object
{
	float m_life;
	float m_defense;

public:
	Bunker();
	Bunker(OBJ_TAG tag);
	~Bunker();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);
};

