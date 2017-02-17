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

	float m_z;	// �� ��� ������ ���� ���� ���� �������ָ�, ũ������ zMin�� zMax�� ���Ͽ� �浹ó���ϵ��� ��

	float m_t;//���ư� �Ÿ� ���� �Ҽ���
	Vector m_moveDirection;
	Vector m_startPos;//���� ��ġ	// startPos�� ��������. ũ���Ĳ� �״�� ������� �ݴ���

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
	void SetStartPos(Vector pos) { m_startPos = pos; }			// startPos�� ��������. ũ���Ĳ� �״�� ������� �ݴ���
	Vector GetStartPos() { return m_startPos; }					// startPos�� ��������. ũ���Ĳ� �״�� ������� �ݴ���
	Vector GetNowPos() { return  m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);}		// startPos�� ��������. ũ���Ĳ� �״�� ������� �ݴ���
	BOOL Collided();
	void SetMoveSpeed(float speed) { m_moveSpeed = speed; }
};

