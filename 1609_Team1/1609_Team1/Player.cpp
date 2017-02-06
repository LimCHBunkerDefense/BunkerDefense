#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	switch (m_state)
	{
	case CHARACTER_IDLE: IdleState(); break;
	case CHARACTER_REST: RestState(deltaTime); break;
	case CHARACTER_RUN: RunState(deltaTime); break;
	case CHARACTER_THROW: ThrowState(deltaTime); break;
	case CHARACTER_COLLECT: CollectState(); break;
	case CHARACTER_SEARCH: SearchState(); break;
	case CHARACTER_PICKUP: PickupState(); break;
	case CHARACTER_BUILD: BuildState(deltaTime); break;
	case CHARACTER_SEEPROP: SeePropState(); break;
	case CHARACTER_SEEITEMS: SeeItemsState(); break;
	}
}

void Player::Draw(Camera* pCamera)
{

}

void Player::AttackState(float deltaTime)
{

}

void Player::ShopState()
{

}