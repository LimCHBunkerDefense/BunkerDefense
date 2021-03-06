#pragma once
#include "ObjectManager.h"
#include "CreatureDB.h"

class Bullet :
	public Object
{
	BULLET_STATE m_state;
	Sprite* m_pSprite;
	float m_moveSpeed;
	float m_scale;
	float m_attack;
	float m_range;

	float m_z;	// 총 쏘는 시점에 따라 총의 높이 지정해주며, 크리쳐의 zMin과 zMax를 비교하여 충돌처리하도록 함
	float m_addH;

	float m_t;//날아간 거리 비율 소수점
	Vector m_moveDirection;
	Vector m_startPos;//종료 위치	// startPos는 종료점임. 크리쳐꺼 그대로 쓰느라고 반대임

public:
	Bullet();
	Bullet(OBJ_TAG tag);
	~Bullet();

	void Update(float deltaTime);
	BOOL UpdateBool(float deltaTime);
	void Draw(Camera* pCamera);

	void StartPosUpdate();

	void IdleState(float deltaTime);
	bool ExplodeState(float deltaTime);

	void SetMoveDirection(Vector vector) { m_moveDirection = vector; }
	Vector GetMoveDirection() { return m_moveDirection; }
	void SetStartPos(Vector pos) { m_startPos = pos; }			// startPos는 종료점임. 크리쳐꺼 그대로 쓰느라고 반대임
	Vector GetStartPos() { return m_startPos; }					// startPos는 종료점임. 크리쳐꺼 그대로 쓰느라고 반대임
	Vector GetNowPos() { return  m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);}		// startPos는 종료점임. 크리쳐꺼 그대로 쓰느라고 반대임
	BOOL Collided();
	void SetMoveSpeed(float speed) { m_moveSpeed = speed; }
	void SetRange();
};

