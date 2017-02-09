#pragma once
#include "ObjectManager.h"
#include "CreatureDB.h"

class Bullet :
	public Object
{
	CREATURE_STATE m_state;
	Sprite* m_pSprite;
	float m_moveSpeed;
	float m_scale;
	float m_angle;

	float m_t;//���ư� �Ÿ� ���� �Ҽ���
	Vector m_moveDirection;
	Vector m_startPos;//���� ��ġ

public:
	Bullet();
	Bullet(OBJ_TAG tag);
	~Bullet();

	void Update(float deltaTime);
	BOOL UpdateBool(float deltaTime);
	void Draw(Camera* pCamera);

	BOOL IdleState(float deltaTime);
	void HitState(float deltaTime);

	void SetMoveDirection(Vector vector) { m_moveDirection = vector; }
	Vector GetMoveDirection() { return m_moveDirection; }
	void SetStartPos(Vector pos) { m_startPos = pos; }
	Vector GetStartPos() { return m_startPos; }
	BOOL Collided();
};

