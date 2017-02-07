#include "Player.h"



Player::Player()
{
}

Player::Player(OBJ_TAG tag) : Object(tag)
{
	m_state = PLAYER_ATTACK;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	switch (m_state)
	{
	case PLAYER_ATTACK: AttackState(deltaTime); break;
	case PLAYER_SHOP: ShopState(); break;
	}

	//Animation()->Update(deltaTime);
}

void Player::Draw(Camera* pCamera)
{
	RENDER->FillCircle(Position(), 100, ColorF::Aqua);
}

void Player::AttackState(float deltaTime)
{
	//Animation()->Play(PLAYER_ATTACK);


	// 씬 채인지
	if (INPUT->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene(SCENE_SHOP);
		m_state = PLAYER_SHOP;
	}

	// 충돌체 On/Off
	if (INPUT->IsKeyDown('0'))
	{
		SCENE->SetColliderOnOff();
	}
}

void Player::ShopState()
{
	//Animation()->Play(PLAYER_SHOP);
	
	// 씬 채인지
	if (INPUT->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene(SCENE_PLAY);
		m_state = PLAYER_ATTACK;
	}

	// 충돌체 On/Off
	if (INPUT->IsKeyDown('0'))
	{
		SCENE->SetColliderOnOff();
	}

	// 마우스 왼쪽 버튼 클릭
	if (INPUT->IsMouseUp(MOUSE_LEFT))
	{
		// if (MATH->IsCollided(Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y), SCENE->GetScene(SCENE_SHOP)->GetButton()))
		// {
		// 	SCENE->SetColliderOnOff();
		// }
	}
}