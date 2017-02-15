#pragma once
#include "ObjectManager.h"
#include "SceneManager.h"
#include "CreatureDB.h"

class Creature :
	public Object
{
	float m_attack;
	float m_defense;
	wstring m_name;
	Sprite* m_pSprite;
	float m_attackCoolTime;
	float m_attackSpeed;
	float m_moveSpeed;
	int m_money;
	int m_score;

	Vector m_startPos;
	float m_scale;
	float m_t;
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

	void StartPosUpdate();
	void SetStartPos(Vector pos) { m_startPos = pos; }
	Vector GetStartPos() { return m_startPos; }
	float GetMT() { return m_t; }

	int GetScore() { return m_score; }
	int GetMoney() { return m_money; }

	//콜라이더 각도 구해서 리턴
	float GetCollideAngle() {
		Vector pos = m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;
		Vector box = (Collider().size * (m_t *2.0f))/2;
		Vector v_center = Position() - OBJECT->GetPlayer()->Position();
		Vector v_side = box + pos - OBJECT->GetPlayer()->Position();
		float a = MATH->CosAngle(v_center, v_side) * 2;
		return a;
	}

};

