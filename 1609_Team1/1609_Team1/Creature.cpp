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

	// ī�޶� ȸ���� ���� ũ���� StartPos ������Ʈ
	StartPosUpdate();


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
	SetCollider(Collider().size * (m_t *3.0f) / m_scale, Collider().anchor);
	SetScale(m_t *3.0f);
	m_scale = m_t *3.0f;

	pCamera->Draw3D(Animation()->Current()->GetSprite(), m_startPos, m_t, OBJECT->GetSightHeight(), m_state);
}

void Creature::IdleState(float deltaTime)
{
	Animation()->Play(CREATURE_IDLE);
}

void Creature::RunState(float deltaTime)
{
	if(m_t >= 0.95) m_state = CREATURE_ATTACK;

	// ũ���� �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);

	// ũ������ ���� ��ġ�� �̴ϸ� �󿡼� �̵�
	Vector pos = m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;
	SetPosition_Creature(pos, pos * 5);


	Animation()->Play(CREATURE_RUN);
}

void Creature::AttackState(float deltaTime)
{
	// ũ������ ���� ��ġ�� �̴ϸ� �󿡼� �̵�
	Vector pos = m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;
	SetPosition_Creature(pos, pos * 5);

	m_attackCoolTime -= deltaTime;
	if (m_attackCoolTime <= 0)
	{
		m_state = CREATURE_RUN;
		m_attackCoolTime = m_attackSpeed;
	}

	Animation()->Play(CREATURE_ATTACK);
}

void Creature::DeadState(float deltaTime)
{
	Animation()->Play(CREATURE_DEAD);
}

// ī�޶� ȸ���� ���� StartPos ������Ʈ
void Creature::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection * -1);
	angle += OBJECT->GetDeltaSightAngle();

	// �� p(0,0)�� �������� ������ ���ο� pos�� �÷��̾� ���� p'(MINI_WIDTH * 0.5, MINI_HEIGHT) �������� (*it)�� ��ǥ ����
	Vector pos = MATH->ToDirection(angle) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();

	m_startPos = pos;
}
