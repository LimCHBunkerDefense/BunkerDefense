#pragma once
#include "ObjectManager.h"
#include "CreatureDB.h"

class Creature :
	public Object
{
	int m_creatureID;
	float m_attack;
	float m_defense;
	wstring m_name;
	Sprite* m_pSprite;

	CREATURE_STATE m_state;
	DIRECTION_TAG m_dir;

public:
	Creature();
	Creature(int creatureID);
	~Creature();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void RunState(float deltaTime);
	void AttackState(float deltaTime);
	void DeadState(float deltaTime);

};

