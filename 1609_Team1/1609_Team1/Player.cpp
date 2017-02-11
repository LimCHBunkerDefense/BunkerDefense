#include "Player.h"



Player::Player()
{
}

Player::Player(OBJ_TAG tag) : Object(tag)
{
	m_state = PLAYER_ATTACK;
	
	m_prevMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	m_sight = SIGHT;

	//m_pItem = OBJECT->CreateItem(GUN_PISTOL, 1001);
	//AddItem(m_pItem);
	//SetAnimation(m_pItem->Animation());
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

	// �� ���� �Լ�
	SetItem();

	// �浹ü On/Off
	if (INPUT->IsKeyDown(VK_0))
	{
		SCENE->SetColliderOnOff();
	}

	//��Ŭ���� �߻� �κ�
	if (INPUT->IsMouseUp(MOUSE_LEFT)) {
		Vector pos = MATH->ToDirection(90) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
		OBJECT->CreateBullet(OBJ_BULLET, pos);
	}

	
	// ���콺 �����̸� ��� ������Ʈ���� �÷��̾� �߽����� ȸ���ϴ� ó�� ����---------------------------------------------------
	// ���� ���콺��ǥ�� ������ ���콺 ��ǥ�� ���ϴ� �κ�
	float fTurnSpeed = 0;
	float deltaHeight = 0;
	Vector NowMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);

	if (abs(NowMousePos.x - m_prevMousePos.x) >EPSILON
		&& NowMousePos.x < m_prevMousePos.x) 
	{
		fTurnSpeed = -ROTATE_SPEED * deltaTime;
	}
	if (abs(NowMousePos.x - m_prevMousePos.x) >EPSILON
		&& NowMousePos.x > m_prevMousePos.x) 
	{
		fTurnSpeed = +ROTATE_SPEED * deltaTime;
	}
	if (abs(NowMousePos.y - m_prevMousePos.y) >EPSILON
		&& NowMousePos.y < m_prevMousePos.y) 
	{
		deltaHeight += ROTATE_SPEED * deltaTime;
		OBJECT->SetSightHeight(OBJECT->GetSightHeight() + ROTATE_SPEED * deltaTime);
	}
	if (abs(NowMousePos.y - m_prevMousePos.y) >EPSILON
		&& NowMousePos.y > m_prevMousePos.y) 
	{
		deltaHeight -= ROTATE_SPEED * deltaTime;
		OBJECT->SetSightHeight(OBJECT->GetSightHeight() - ROTATE_SPEED * deltaTime);
	}
	
	if(abs(fTurnSpeed) > EPSILON) OBJECT->SetDeltaSightAngle(fTurnSpeed);
	if (abs(deltaHeight) > EPSILON) OBJECT->SetDeltaSightHeight(deltaHeight);
	

	m_prevMousePos = NowMousePos;

	// Ŀ�� ȭ�� ������ ������ �ʵ��� ����
	if (m_prevMousePos.x <= 100
		|| m_prevMousePos.x >= 1000
		|| m_prevMousePos.y < 100
		|| m_prevMousePos.y> 800)
	{
		SetCursorPos(500, 500);
		m_prevMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	}

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
		int but;
		list<Box*> boxList = SCENE->GetScene(SCENE_SHOP)->GetBoxList();
		for (list<Box*>::iterator it_Box = boxList.begin(); it_Box != boxList.end(); it_Box++)
		{
			if (MATH->IsCollided(Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y), *(*it_Box)))
			{
				list<Object*> itemList = OBJECT->GetShopItemList();
				switch ((*it_Box)->buttonTag)
				{
				case BUTTON_WEAPON:
					SCENE->GetScene(SCENE_SHOP)->SetCurrentButton(BUTTON_WEAPON);
					but = SCENE->GetScene(SCENE_SHOP)->GetCurrentButton();
					SCENE->GetScene(SCENE_SHOP)->SetIsWeaponClicked(true);
					SCENE->GetScene(SCENE_SHOP)->SetIsBulletClicked(false);
					SCENE->GetScene(SCENE_SHOP)->SetIsUsingItemClicked(false);
					break;
				case BUTTON_BULLET:
					SCENE->GetScene(SCENE_SHOP)->SetCurrentButton(BUTTON_BULLET);
					SCENE->GetScene(SCENE_SHOP)->SetIsWeaponClicked(false);
					SCENE->GetScene(SCENE_SHOP)->SetIsBulletClicked(true);
					SCENE->GetScene(SCENE_SHOP)->SetIsUsingItemClicked(false);
					break;
				case BUTTON_USINGITEM:
					SCENE->GetScene(SCENE_SHOP)->SetCurrentButton(BUTTON_USINGITEM);
					SCENE->GetScene(SCENE_SHOP)->SetIsWeaponClicked(false);
					SCENE->GetScene(SCENE_SHOP)->SetIsBulletClicked(false);
					SCENE->GetScene(SCENE_SHOP)->SetIsUsingItemClicked(true);
					break;
				case BUTTON_FIRST:
					if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked())
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
				case BUTTON_SECOND:
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
				case BUTTON_THIRD:
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
				case BUTTON_FORTH:
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
				case BUTTON_BUY:// �������� ���� �����ϸ� �� �������� ������ ���濡 �����
					if (m_itemBag.find(SCENE->GetScene(SCENE_SHOP)->GetSelectedItem()->GetID()) != m_itemBag.end())
					{
						Object* pItem = SCENE->GetScene(SCENE_SHOP)->GetSelectedItem();
						AddItem(pItem);
						break;
					}

				case BUTTON_EXIT:
					break;				
				}
			}
		}
	}
}

void Player::SetItem()
{
	// ���� ����
	if (INPUT->IsKeyDown(VK_1))
	{
		if (m_itemBag.find(1001) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1001];
		}
	}

	// ����� ����
	if (INPUT->IsKeyDown(VK_2))
	{
		if (m_itemBag.find(1002) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1002];
		}
	}

	// ȭ�� ���� ����
	if (INPUT->IsKeyDown(VK_3))
	{
		if (m_itemBag.find(1003) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1003];
		}
	}

	// ������ �� ����
	if (INPUT->IsKeyDown(VK_4))
	{
		if (m_itemBag.find(1004) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1004];
		}
	}

}