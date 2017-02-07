#include "Player.h"



Player::Player():
	m_LineCamera(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(90) * 600),
	m_LineLeft(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(CAMERA_LEFT) * 600),
	m_LineRight(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(CAMERA_RIGHT) * 600)
{
}

Player::Player(OBJ_TAG tag) : Object(tag),
m_LineCamera(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(90) * 600),
m_LineLeft(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(CAMERA_LEFT) * 600),
m_LineRight(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(CAMERA_RIGHT) * 600)
{
	m_state = PLAYER_ATTACK;
	m_dir=Vector::Right();
	m_height = GROUND_HEIGHT;
	PrevMousePos = INPUT->GetMousePos();
	Sight = SIGHT;
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


	// �� ä����
	if (INPUT->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene(SCENE_SHOP);
		m_state = PLAYER_SHOP;
	}

	// �浹ü On/Off
	if (INPUT->IsKeyDown('0'))
	{
		SCENE->SetColliderOnOff();
	}

	//���콺 ������ ���� ���ư���
	float fTurnSpeed = 0;
	if (INPUT->IsKeyPress(VK_LEFT)) {
		//m_angle -= 10 * deltaTime;
		fTurnSpeed = -ROTATE_SPEED;
	}
	if (INPUT->IsKeyPress(VK_RIGHT)) {
		//m_angle += 10 * deltaTime;
		fTurnSpeed = ROTATE_SPEED;
	}
	if (INPUT->IsKeyPress(VK_UP)) {
		//m_angle -= 10 * deltaTime;
		m_height += ROTATE_SPEED * 5;
	}
	if (INPUT->IsKeyPress(VK_DOWN)) {
		//m_angle += 10 * deltaTime;
		m_height -= ROTATE_SPEED * 5;
	}
	/*FOR_LIST(Line*, m_listLine) {
		float prev_angle = MATH->Angle(m_dir, (*it)->EndPoint() - (*it)->StartPoint());
		Vector result_dir = MATH->ToDirection(prev_angle + fTurnSpeed);
		(*it)->SetEndPoint(m_player.center + result_dir * 600);
	}*/
}

void Player::ShopState()
{
	//Animation()->Play(PLAYER_SHOP);
	
	// �� ä����
	if (INPUT->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene(SCENE_PLAY);
		m_state = PLAYER_ATTACK;
	}

	// �浹ü On/Off
	if (INPUT->IsKeyDown('0'))
	{
		SCENE->SetColliderOnOff();
	}

	// ���콺 ���� ��ư Ŭ��
	if (INPUT->IsMouseUp(MOUSE_LEFT))
	{
		if (MATH->IsCollided(Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y), SCENE->GetScene(SCENE_SHOP)->GetButton()))
		{
			SCENE->SetColliderOnOff();
		}
	}
}