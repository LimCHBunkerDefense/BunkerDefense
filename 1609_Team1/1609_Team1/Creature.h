#pragma once
#include "ObjectManager.h"
#include "CreatureDB.h"

class Creature :
	public Object
{
	float m_attack;
	float m_defense;
	wstring m_name;
	Sprite* m_pSprite;
	float m_attackSpeed;
	float m_attackCoolTime;
	float m_moveSpeed;

	float m_scale;
	CREATURE_STATE m_state;
	DIRECTION_TAG m_dir;
	Vector m_moveDirection;

public:
	Creature();
	Creature(OBJ_TAG tag);
	~Creature();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void IdleState(float deltaTime);
	void RunState(float deltaTime);
	void AttackState(float deltaTime);
	void DeadState(float deltaTime);

	void SetMoveDirection(Vector vector) { m_moveDirection = vector; }
	Vector GetMoveDirection() { return m_moveDirection; }

};

