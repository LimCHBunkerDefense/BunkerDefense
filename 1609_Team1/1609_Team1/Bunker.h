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

	float GetLife() { return m_life; }
	void AddLife(float addLife) { m_life += addLife; }
	float GetDefense() { return m_defense; }
	void AddDefense(float addDefense) { m_defense += addDefense; }
};

