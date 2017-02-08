#include "Player.h"



Player::Player()
{
}

Player::Player(OBJ_TAG tag) : Object(tag)
{
	m_state = PLAYER_ATTACK;
	m_vAngle =Vector::Right();
	
	m_prevMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
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
	RENDER->FillCircle(Position() * 5, 100, ColorF::Aqua);
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
	if (INPUT->IsKeyDown(VK_0))
	{
		SCENE->SetColliderOnOff();
	}

	// ���콺 �����̸� ��� ������Ʈ���� �÷��̾� �߽����� ȸ���ϴ� ó�� ����---------------------------------------------------
	// ���� ���콺��ǥ�� ������ ���콺 ��ǥ�� ���ϴ� �κ�
	float fTurnSpeed = 0;
	Vector NowMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	if (NowMousePos.x < m_prevMousePos.x) {
		fTurnSpeed = -ROTATE_SPEED;
	}
	if (NowMousePos.x > m_prevMousePos.x) {
		fTurnSpeed = +ROTATE_SPEED;
	}
	if (NowMousePos.y < m_prevMousePos.y) {
		m_height += ROTATE_SPEED;
	}
	if (NowMousePos.x > m_prevMousePos.x) {
		m_height -= ROTATE_SPEED;
	}
	m_angle += fTurnSpeed;

	// ũ���� ����Ʈ �ҷ��ٰ� �̴ϸ� ���� pos �������ִ� �κ�
	list<Object*> creatureList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, creatureList)
	{
		float angle = MATH->Angle(Vector::Right(), (*it)->GetMoveDirection() * -1);
		angle += fTurnSpeed;

		// �� p(0,0)�� �������� ������ ���ο� pos�� �÷��̾� ���� p'(MINI_WIDTH * 0.5, MINI_HEIGHT) �������� (*it)�� ��ǥ ����
		float x = MINI_WIDTH*0.5f + MATH->Cos(angle) * MINI_WIDTH * 0.5f;
		float y = MINI_HEIGHT +  MATH->Sin(angle) * MINI_WIDTH * 0.5f;

		(*it)->SetStartPos(Vector(x, y));
	}
	m_prevMousePos = NowMousePos;

	// ���콺 �����̸� ��� ������Ʈ���� �÷��̾� �߽����� ȸ���ϴ� ó�� ��---------------------------------------------------
	
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
	if (INPUT->IsKeyDown(VK_0))
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
				switch ((*it_Box)->index)
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
				case 4:
					if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1001);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsBulletClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1005);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsUsingItemClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1009);
					}
					break;
				case 5:
					if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1002);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsBulletClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1006);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsUsingItemClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1010);
					}
					break;
				case 6:
					if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1003);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsBulletClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1007);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsUsingItemClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1011);
					}
					break;
				case 7:
					if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1004);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsBulletClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1008);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsUsingItemClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1012);
					}
					break;
				case 8:// �������� ���� �����ϸ� �� �������� ������ ���濡 �����
					   //	if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked() == true)
					   //	{
					   //		Item* pItem = SCENE->GetScene(SCENE_SHOP)->GetSelectedItem();
					   //		AddItem(pItem);
					   //	}
					break;
				}
			}
		}
	}
}