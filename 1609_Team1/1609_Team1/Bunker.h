#pragma once
#include "ObjectManager.h"
class Bunker :
	public Object
{
	float m_currentLife;
	float m_maxLife;
	float m_defense;

public:
	Bunker();
	Bunker(OBJ_TAG tag);
	~Bunker();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	float GetMaxLife() { return m_maxLife; }
	float GetCurrentLife() { return m_currentLife; }
	void AddCurrentLife(float addLife) { m_currentLife = MATH->Clamp(m_currentLife + addLife, 0.0f, 1000.0f); }
	void AddMaxLife(float addLife) { m_maxLife; }
	float GetDefense() { return m_defense; }
	void AddDefense(float addDefense) { m_defense += addDefense; }
};

