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
}


Creature::~Creature()
{
}

void Creature::Update(float deltaTime)
{
	switch (m_state)
	{
	case CREATURE_ATTACK: AttackState(deltaTime); break;
	case CREATURE_RUN: RunState(deltaTime); break;
	case CREATURE_DEAD: DeadState(deltaTime); break;

	}

	m_scale = MATH->Clamp(m_scale + 0.01f, 0.5f, 1.5f);
	SetScale(m_scale);
	Animation()->Update(deltaTime);
}

void Creature::Draw(Camera* pCamera)
{
	pCamera->Draw(Animation()->Current()->GetSprite(), Position(), m_dir);
}

void Creature::RunState(float deltaTime)
{
	Animation()->Play(CREATURE_RUN);
}

void Creature::AttackState(float deltaTime)
{
	Animation()->Play(CREATURE_ATTACK);
}

void Creature::DeadState(float deltaTime)
{
	Animation()->Play(CREATURE_DEAD);
}
