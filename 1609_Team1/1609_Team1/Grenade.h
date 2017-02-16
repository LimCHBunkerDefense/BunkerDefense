#pragma once
#include "ObjectManager.h"
#include "CreatureDB.h"

class Grenade :
	public Object
{
	GRENADE_STATE m_state;
	Sprite* m_pSprite;
	float m_moveSpeed;
	float m_scale;
	float m_goal;
	float m_addHeight;
	float m_explodetime;//폭파시간
	float m_t;//날아간 거리 비율 소수점
	Vector m_moveDirection;
	Vector m_startPos;//시작 위치

public:
	Grenade();
	Grenade(OBJ_TAG tag);
	~Grenade();

	void Update(float deltaTime);
	BOOL UpdateBool(float deltaTime);
	void Draw(Camera* pCamera);

	void IdleState(float deltaTime);
	BOOL HitState(float deltaTime);

	void SetMoveDirection(Vector vector) { m_moveDirection = vector; }
	Vector GetMoveDirection() { return m_moveDirection; }
	void SetStartPos(Vector pos) { m_startPos = pos; }
	Vector GetStartPos() { return m_startPos; }
	Vector GetNowPos() { return  m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t); }
	void SetGoal(float goal) { m_goal = goal; }
	void Collided();
	void StartPosUpdate();
};

