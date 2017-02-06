#pragma once
#include "ObjectManager.h"
class Creature :
	public Object
{
	CREATURE_STATE m_state;
	DIRECTION_TAG m_dir;

public:
	Creature();
	~Creature();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void RunState(float deltaTime);
	void AttackState(float deltaTime);
	void DeadState(float deltaTime);

};

