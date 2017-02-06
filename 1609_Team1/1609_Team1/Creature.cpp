#include "Creature.h"



Creature::Creature()
{
}


Creature::~Creature()
{
}

void Creature::Update(float deltaTime)
{
	switch (m_state)
	{
	case PLAYER_ATTACK: AttackState(deltaTime); break;
	case PLAYER_SHOP: ShopState(); break;

	}
}

void Creature::Draw(Camera* pCamera)
{

}
