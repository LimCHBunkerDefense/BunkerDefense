#include "Player.h"



Player::Player()
{
}

Player::Player(OBJ_TAG tag) : Object(tag)
{
	m_state = PLAYER_ATTACK;
	m_vAngle =Vector::Right();
	
	PrevMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	Sight = SIGHT;
	m_angle = 0;
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
	//ColorF lineColor = MATH->IsCollided(m_player, m_LeftLine) ? ColorF::DeepPink : ColorF::Green;
	/*RENDER->DrawInMap(m_LineCamera, ColorF::Red, 2);
	RENDER->DrawInMap(m_LineLeft, ColorF::Blue, 2);
	RENDER->DrawInMap(m_LineRight, ColorF::Blue, 2);*/


	//����
	/*FOR_LIST(Line*, m_listLine) {
		float now_angle = MATH->Angle(m_dir, (*it)->EndPoint() - (*it)->StartPoint());
		RENDER->DrawInMap(*(*it), ColorF::Red);
		if (now_angle <= CAMERA_LEFT && now_angle >= CAMERA_RIGHT) {

			if (now_angle <= 90)	RENDER->Draw3D(m_LineCamera, m_LineLeft, *(*it), m_height, ColorF::Red);
			else					RENDER->Draw3D(m_LineCamera, m_LineRight, *(*it), m_height, ColorF::Red, false);
		}
	}

	RENDER->DrawInMap(m_player, ColorF::Aqua);
	RENDER->Draw(m_player, ColorF::Aqua);*/
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

	//������ ����
	if (INPUT->IsKeyDown(VK_F4))
	{
		PostQuitMessage(0);
	}

	// �浹ü On/Off
	if (INPUT->IsKeyDown('0'))
	{
		SCENE->SetColliderOnOff();
	}

	//���콺 ������ ���� ���ư���
	float fTurnSpeed = 0;
	Vector NowMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	if (NowMousePos.x < PrevMousePos.x) {
		fTurnSpeed = -ROTATE_SPEED;
	}
	if (NowMousePos.x > PrevMousePos.x) {
		fTurnSpeed = +ROTATE_SPEED;
	}
	if (NowMousePos.y < PrevMousePos.y) {
		m_height += ROTATE_SPEED;
	}
	if (NowMousePos.x > PrevMousePos.x) {
		m_height -= ROTATE_SPEED;
	}
	if (INPUT->IsKeyPress(VK_LEFT)) {
		fTurnSpeed = -ROTATE_SPEED;
	}
	if (INPUT->IsKeyPress(VK_RIGHT)) {
		fTurnSpeed = ROTATE_SPEED;
	}
	m_angle += fTurnSpeed;
	
	/* ũ���� ����Ʈ ���� Line���� �޾ƿͼ� ȸ�����Ѽ� ����ؾ���*/
	list<Object*> CreatureList=OBJECT->GetCreatureList();
	FOR_LIST(Object*, CreatureList) {
		float prev_angle = MATH->Angle(Position()-(*it)->GetStartPos(), Vector::Up());
		Vector result_dir = MATH->ToDirection(prev_angle + fTurnSpeed);
		(*it)->SetStartPos(MATH->ToDirection(prev_angle + fTurnSpeed*MINI_WIDTH));
		//(*it)->SetPosition(MATH->ToDirection(prev_angle + fTurnSpeed*MINI_WIDTH));
		//(*it)->SetMoveDirection(Vector(CHARACTER_X, CHARACTER_Y) + result_dir * 600);
	}
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
		list<Box*> boxList = SCENE->GetScene(SCENE_SHOP)->GetBoxList();
		for (list<Box*>::iterator it_Box = boxList.begin(); it_Box != boxList.end(); it_Box++)
		{
			if (MATH->IsCollided(Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y), *(*it_Box)))
			{
				list<Item*> itemList = SCENE->GetScene(SCENE_SHOP)->GetItemList();
				switch ((*it_Box)->itemTag)
				{
				case ITEM_WEAPON:
					SCENE->GetScene(SCENE_SHOP)->SetCurrentButton(BUTTON_WEAPON);
					SCENE->GetScene(SCENE_SHOP)->SetIsWeaponClicked(true);
					SCENE->GetScene(SCENE_SHOP)->SetIsBulletClicked(false);
					SCENE->GetScene(SCENE_SHOP)->SetIsUsingItemClicked(false); 
					break;
				case ITEM_BULLET:
					SCENE->GetScene(SCENE_SHOP)->SetCurrentButton(BUTTON_BULLET);
					SCENE->GetScene(SCENE_SHOP)->SetIsWeaponClicked(false);
					SCENE->GetScene(SCENE_SHOP)->SetIsBulletClicked(true);
					SCENE->GetScene(SCENE_SHOP)->SetIsUsingItemClicked(false);
					break;
				case ITEM_USINGITEM:
					SCENE->GetScene(SCENE_SHOP)->SetCurrentButton(BUTTON_USINGITEM);
					SCENE->GetScene(SCENE_SHOP)->SetIsWeaponClicked(false);
					SCENE->GetScene(SCENE_SHOP)->SetIsBulletClicked(false);
					SCENE->GetScene(SCENE_SHOP)->SetIsUsingItemClicked(true);
					break;
				}
			}

		}
	}
}