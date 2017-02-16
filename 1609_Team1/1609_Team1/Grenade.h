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
	float m_explodetime;
	float m_explodeEnd; //���� ������ �ð�
	float m_explodeSize; //���Ļ�����
	float m_t;//���ư� �Ÿ� ���� �Ҽ���
	Vector m_moveDirection;
	Vector m_startPos;//���� ��ġ

public:
	Grenade();
	Grenade(OBJ_TAG tag, GRENADE_STATE gre_state);
	~Grenade();

	void Update(float deltaTime);
	BOOL UpdateBool(float deltaTime);
	void Draw(Camera* pCamera);

	void IdleState(float deltaTime);
	BOOL HitState(float deltaTime);
	GRENADE_STATE GetStateExplode(GRENADE_STATE gre_state);

	void SetMoveDirection(Vector vector) { m_moveDirection = vector; }
	Vector GetMoveDirection() { return m_moveDirection; }
	void SetStartPos(Vector pos) { m_startPos = pos; }
	Vector GetStartPos() { return m_startPos; }
	Vector GetNowPos() { return  m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t); }
	void SetGoal(float goal) { m_goal = goal; }
	void Collided();
	void StartPosUpdate();
};

