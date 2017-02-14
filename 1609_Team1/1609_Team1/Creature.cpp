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
	// 크리쳐 이동방향벡터 실시간 업데이트
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	// 카메라 회전에 따른 크리쳐 StartPos 업데이트
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
	// 크리처 스케일 변화되는 부분
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

	// 크리쳐 이동에 관계된 비율 (시작점에서 플레이어까지 가는 거리를 1로 봤을 때, 현재 이동한 거리의 비율)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);

	// 크리쳐의 현재 위치를 미니맵 상에서 이동
	Vector pos = m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;
	SetPosition_Creature(pos, pos * 5);


	Animation()->Play(CREATURE_RUN);
}

void Creature::AttackState(float deltaTime)
{
	// 크리쳐의 현재 위치를 미니맵 상에서 이동
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

// 카메라 회전에 의한 StartPos 업데이트
void Creature::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection * -1);
	angle += OBJECT->GetDeltaSightAngle();

	// 점 p(0,0)를 기준으로 구해진 새로운 pos를 플레이어 위지 p'(MINI_WIDTH * 0.5, MINI_HEIGHT) 기준으로 (*it)의 좌표 보정
	Vector pos = MATH->ToDirection(angle) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();

	m_startPos = pos;
}
