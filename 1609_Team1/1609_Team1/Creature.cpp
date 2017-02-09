#include "Creature.h"



Creature::Creature()
{
	m_state = CREATURE_RUN;
	m_dir = DIRECTION_CENTER;
}

Creature::Creature(OBJ_TAG tag) : Object(tag)
{
	CreatureData* pData = CREATURE->GetData(tag);
	m_state = CREATURE_RUN;
	m_dir = DIRECTION_CENTER;

	m_scale = 0.5f;
	m_t = 0.0f;
	m_attack = pData->attack;
	m_defense = pData->defense;
	m_name = pData->name;
	m_attackSpeed = pData->attackSpeed;
	m_attackCoolTime = m_attackSpeed;
	m_moveSpeed = pData->moveSpeed;

	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
	
}


Creature::~Creature()
{
}

void Creature::Update(float deltaTime)
{
	// ũ���� �̵����⺤�� �ǽð� ������Ʈ
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();


	switch (m_state)
	{
	case CREATURE_IDLE: IdleState(deltaTime); break;
	case CREATURE_ATTACK: AttackState(deltaTime); break;
	case CREATURE_RUN: RunState(deltaTime); break;
	case CREATURE_DEAD: DeadState(deltaTime); break;

	}

	Animation()->Update(deltaTime);
}

void Creature::Draw(Camera* pCamera)
{
	// ũ��ó ������ ��ȭ�Ǵ� �κ�
	SetCollider(Collider().size * (m_t *2.0f) / m_scale, Collider().anchor);
	SetScale(m_t *2.0f);
	m_scale = m_t *2.0f;

	pCamera->Draw3D(Animation()->Current()->GetSprite(), Position());
	//pCamera->Draw3DLine(Animation()->Current()->GetSprite(), m_moveLine, m_dir);
}

void Creature::IdleState(float deltaTime)
{
	Animation()->Play(CREATURE_IDLE);
}

void Creature::RunState(float deltaTime)
{
	//if (Animation()->Current()->GetSprite()->GetScale() >= 0.9999) 
	//m_state = CREATURE_ATTACK;

	// ũ���� �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);

	// ũ������ ���� ��ġ�� �̴ϸ� �󿡼� �̵�
	Vector pos = m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;
	SetPosition_Creature(pos, pos * 5);


	Animation()->Play(CREATURE_RUN);
}

void Creature::AttackState(float deltaTime)
{
	Animation()->Play(CREATURE_ATTACK);
	m_attackCoolTime -= deltaTime;
	if (m_attackCoolTime <= 0)
	{
		m_state = CREATURE_RUN;
		m_attackCoolTime = m_attackSpeed;
	}
}

void Creature::DeadState(float deltaTime)
{
	Animation()->Play(CREATURE_DEAD);
}
