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

	float m_t;//���ư� �Ÿ� ���� �Ҽ���
	float m_goal;//���� ��ġ���� ����
	Vector m_moveDirection;
	Vector m_startPos;//���� ��ġ

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
	BOOL Collided();
};

