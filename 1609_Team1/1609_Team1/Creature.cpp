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
	// 크리쳐 이동방향벡터 실시간 업데이트
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
	// 크리처 스케일 변화되는 부분
	float changedScale = MATH->Clamp(m_scale + 0.003f, 0.5f, 1.0f);
	SetCollider(Collider().size * changedScale / m_scale, Collider().anchor);
	m_scale = changedScale;
	SetScale(m_scale);

	pCamera->Draw3D(Animation()->Current()->GetSprite(), Position(), m_dir);
}

void Creature::IdleState(float deltaTime)
{
	Animation()->Play(CREATURE_IDLE);
}

void Creature::RunState(float deltaTime)
{
	if (Animation()->Current()->GetSprite()->GetScale() >= 0.9999) m_state = CREATURE_ATTACK;
	Vector pos = Position() + m_moveDirection * m_moveSpeed * deltaTime;
	SetPosition(pos);
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
