#include "Creature.h"



Creature::Creature()
{
	m_state = CREATURE_RUN;
	m_dir = DIRECTION_CENTER;
}

Creature::Creature(int creatureID)
{
	CreatureData* pData = CREATURE->GetData(creatureID);
	m_state = CREATURE_RUN;
	m_dir = DIRECTION_CENTER;

	m_creatureID = pData->creatureID;
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
