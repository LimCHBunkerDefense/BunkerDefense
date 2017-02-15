#include "Player.h"



Player::Player()
{
}

Player::Player(OBJ_TAG tag) : Object(tag)
{
	m_state = PLAYER_ATTACK;
	item_state = ITEM_PISTOL;

	HitPoint = 10;
	
	m_prevMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	HitPoint = 100;
	//m_sight = SIGHT;

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
	//case PLAYER_THROW: ThrowState(deltaTime); break;
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
		if (IsThrow) {
			Vector pos = MATH->ToDirection(90) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
			OBJECT->CreateGrenade(OBJ_GRENADE, pos);
			IsThrow = false;
		}
		else {
			Vector pos = MATH->ToDirection(90) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
			OBJECT->CreateBullet(OBJ_BULLET, pos);
		}
	}

	
	// ���콺 �����̸� ��� ������Ʈ���� �÷��̾� �߽����� ȸ���ϴ� ó�� ����---------------------------------------------------
	// Ŀ�� ȭ�� ������ ������ �ʵ��� ����. �̰� ������ ���콺 ������ǥ�� ������ǥ�� ������ ����ϴ� �κ��� �տ� �־�� ��.
	if (m_prevMousePos.x <= 100
		|| m_prevMousePos.x >= 1000
		|| m_prevMousePos.y < 100
		|| m_prevMousePos.y> 800)
	{
		SetCursorPos(500, 500);
		m_prevMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	}
	
	// ���� ���콺��ǥ�� ������ ���콺 ��ǥ�� ���ϴ� �κ�
	float fTurnSpeed = 0;
	float deltaHeight = 0;
	Vector NowMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	Vector gap = m_prevMousePos - NowMousePos;

	// ���콺 �������� �������� ��
	if (gap.x > 0) 
	{
		fTurnSpeed = ROTATE_SPEED * deltaTime * gap.x;
	}

	// ���콺 �������� �������� ��
	if (gap.x < 0) 
	{
		fTurnSpeed = ROTATE_SPEED * deltaTime * gap.x;
	}

	// ���콺 �������� �������� ��
	if (gap.y < 0) 
	{
		// ���콺�� ���� ��ȭ�� ���̰� ���
		deltaHeight = ROTATE_SPEED * deltaTime * gap.y * 10;
	}

	// ���콺 �Ʒ������� �������� ��
	if (gap.y > 0) 
	{
		// ���콺�� ���� ��ȭ�� ���̰� ���
		deltaHeight = ROTATE_SPEED * deltaTime * gap.y * 10;
	}
	
	// ���콺 �̵��� ���� ��ȭ������ ������Ʈ �޴����� �������ֱ�. SetDeltaSightAngle�� �̴ϸʿ��� ũ���� ȸ���� ���� ����. 
	OBJECT->SetDeltaSightAngle(fTurnSpeed * -1);
	OBJECT->SetDeltaSightHeight(deltaHeight * -1);

	// �÷��̾ ���� ���̰� ���������ִ� �κ�
	OBJECT->SetSightHeight(deltaHeight);	

	// m_prevMousePos�� ���� Ŀ�� ��ġ�� �ʱ�ȭ
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
				list<Object*> itemList = OBJECT->GetShopItemList();
				switch ((*it_Box)->buttonTag)
				{
				case BUTTON_WEAPON:
					SCENE->GetScene(SCENE_SHOP)->SetCurrentButton(BUTTON_WEAPON);
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

				case BUTTON_COUNT:		// ���� ��ư ���ý� ���� �Է�ĭ Ȱ��ȭ
					SCENE->GetScene(SCENE_SHOP)->SetInputOnOff(true);
					break;

				case BUTTON_BUY:		// �������� ���� �����ϸ� �� �������� ������ ���濡 �����
					if (m_itemBag.find(SCENE->GetScene(SCENE_SHOP)->GetSelectedItem()->GetID()) != m_itemBag.end())
					{
						Object* pItem = SCENE->GetScene(SCENE_SHOP)->GetSelectedItem();
						AddItem(pItem);
						break;
					}

				case BUTTON_EXIT:
					SCENE->ChangeScene(SCENE_PLAY);
					m_state = PLAYER_ATTACK;
					break;				
				}
			}
		}
	}	// switch�� END

	if (SCENE->GetScene(SCENE_SHOP)->GetInputOnOff() == true)
	{
		int num = 0; 
		if (INPUT->IsKeyDown(VK_0)) num = 0;
		if (INPUT->IsKeyDown(VK_1)) num = 1;
		if (INPUT->IsKeyDown(VK_2)) num = 2;
		if (INPUT->IsKeyDown(VK_3)) num = 3;
		if (INPUT->IsKeyDown(VK_4)) num = 4;
		if (INPUT->IsKeyDown(VK_5)) num = 5;
		if (INPUT->IsKeyDown(VK_6)) num = 6;
		if (INPUT->IsKeyDown(VK_7)) num = 7;
		if (INPUT->IsKeyDown(VK_8)) num = 8;
		if (INPUT->IsKeyDown(VK_9)) num = 9;

		if(num != 0) SCENE->GetScene(SCENE_SHOP)->SetInputCount(num);

	}	// InputCount Bool�Լ� END
}

void Player::SetItem()
{
	// ���� ����
	if (INPUT->IsKeyDown(VK_1))
	{
		item_state = ITEM_PISTOL;
		if (m_itemBag.find(1001) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1001];
		}
	}

	// ����� ����
	if (INPUT->IsKeyDown(VK_2))
	{
		item_state = ITEM_MACHINEGUN;
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
		item_state = ITEM_LASERGUN;
		if (m_itemBag.find(1004) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1004];
		}
	}

	if (INPUT->IsKeyDown(VK_Q))
	{
		IsThrow = true;
	}

}