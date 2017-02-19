#include "Player.h"



Player::Player()
{
}

Player::Player(OBJ_TAG tag) : Object(tag)
{
	ani_state = IDLE_PISTOL;
	m_greCoolTime = 0.0f;//����ź ��Ÿ��
	m_state = PLAYER_ATTACK;
	item_state = ITEM_PISTOL;

	HitPoint = 10;
	
	m_prevMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	HitPoint = 100;
	//m_sight = SIGHT;

	m_pItem = OBJECT->CreateItem(ITEM_PISTOL, 1001);
	// SetAnimation(m_pItem->Animation());
	AddItem(m_pItem);
	
	Object* startBullet = OBJECT->CreateItem(ITEM_PSBULLET, 2001);
	m_itemBag[startBullet->GetTag()] = startBullet;
	startBullet->AddCurrentCount(60);

	m_money = 100000;
	m_score = 0;

	gre_state = GRENADE_NONE;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	m_greCoolTime = MATH->Clamp(m_greCoolTime - deltaTime, 0.0f, 2.0f);
	switch (m_state)
	{
	case PLAYER_ATTACK: AttackState(deltaTime); break;
	//case PLAYER_THROW: ThrowState(deltaTime); break;
	case PLAYER_SHOP: ShopState(); break;
	}

	Animation()->Update(deltaTime);
}

void Player::Draw(Camera* pCamera)
{
	//RENDER->FillCircle(Position() * 5, 100, ColorF::Aqua);
	Vector pos = DrawPos();
	pCamera->Draw(Animation()->Current()->GetSprite(), pos, 1);
}

Vector Player::DrawPos()
{
	Vector pos;
	switch (m_pItem->GetTag())
	{
	case ITEM_PISTOL:
		pos = Vector(VIEW_WIDTH / 2 + 50, VIEW_HEIGHT);
		break;
	case ITEM_SHOTGUN:
		pos = Vector(VIEW_WIDTH / 2 + 30, VIEW_HEIGHT);
		break;
	case ITEM_MACHINEGUN:
		pos = Vector(VIEW_WIDTH / 2, VIEW_HEIGHT);
		break;
	case ITEM_LASERGUN:
		pos = Vector(VIEW_WIDTH / 2 + 30, VIEW_HEIGHT);
		break;
	}
	return pos;
}

void Player::AttackState(float deltaTime)
{
	SetIdleAnimation();
	Animation()->Play(ani_state);

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
	if (INPUT->IsKeyDown(VK_F6))
	{
		SCENE->SetColliderOnOff();
	}

	//��Ŭ���� �߻� �κ�
	if (INPUT->IsMouseUp(MOUSE_LEFT)) {
		if (gre_state != GRENADE_NONE) {
			if (m_greCoolTime == 0.0f) {
				Vector pos = MATH->ToDirection(90) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
				OBJECT->CreateGrenade(OBJ_GRENADE, pos, gre_state);
				m_greCoolTime = 2.0f;
			}
		}
		else {
			float sightHeightDefault = SIGHTHEIGHT_DEFAULT;
			float rate = 1 + MATH->Clamp(OBJECT->GetSightHeight() - sightHeightDefault, sightHeightDefault / 2 * -1, 0.0f) / sightHeightDefault;
			Vector pos = Vector::Up() * m_pItem->GetRange() * rate + OBJECT->GetPlayer()->Position();
			OBJECT->CreateBullet(OBJ_BULLET, pos, m_pItem->GetTag());
			SetShotAnimation();
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
	if (INPUT->IsKeyDown(VK_F6))
	{
		SCENE->SetColliderOnOff();
	}

	map<int, Object*> check;

	// ���콺 ���� ��ư Ŭ��
	if (INPUT->IsMouseUp(MOUSE_LEFT))
	{
		list<Box*> boxList = SCENE->GetScene(SCENE_SHOP)->GetBoxList();
		for (list<Box*>::iterator it_Box = boxList.begin(); it_Box != boxList.end(); it_Box++)
		{
			if (MATH->IsCollided(Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y), *(*it_Box)))
			{
				list<Object*> itemList = OBJECT->GetShopItemList();
				Object* pItem;

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
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(2001);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsUsingItemClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(3001);
					}
					SCENE->GetScene(SCENE_SHOP)->SetIsCountClicked(true);
					break;

				case BUTTON_SECOND:
					if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1002);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsBulletClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(2002);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsUsingItemClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(3002);
					}
					SCENE->GetScene(SCENE_SHOP)->SetIsCountClicked(true);
					break;

				case BUTTON_THIRD:
					if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1003);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsBulletClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(2003);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsUsingItemClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(3003);
					}
					SCENE->GetScene(SCENE_SHOP)->SetIsCountClicked(true);
					break;

				case BUTTON_FORTH:
					if (SCENE->GetScene(SCENE_SHOP)->GetIsWeaponClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(1004);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsBulletClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(2004);
					}
					else if (SCENE->GetScene(SCENE_SHOP)->GetIsUsingItemClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetSelectedItem(3004);
					}
					SCENE->GetScene(SCENE_SHOP)->SetIsCountClicked(true);
					break;

				case BUTTON_COUNT:		// ���� ��ư ���ý� ���� �Է�ĭ Ȱ��ȭ
					if (SCENE->GetScene(SCENE_SHOP)->GetIsCountClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetInputOnOff(true);
					}
					break;

				case BUTTON_BUY:		// �������� ���� �����ϸ� �� �������� ������ ���濡 �����
					pItem = SCENE->GetScene(SCENE_SHOP)->GetSelectedItem();
					AddItem(pItem);
					check = m_itemBag;
					break;				

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
		if (INPUT->IsKeyDown(VK_1))	num = 1;
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
			ani_state = IDLE_PISTOL;
		}
	}

	// ���� ����
	if (INPUT->IsKeyDown(VK_2))
	{
		item_state = ITEM_SHOTGUN;
		if (m_itemBag.find(1002) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1002];
			ani_state = IDLE_SHOT;
		}
	}

	// ����� ����
	if (INPUT->IsKeyDown(VK_3))
	{
		item_state = ITEM_MACHINEGUN;
		if (m_itemBag.find(1003) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1003];
			ani_state = IDLE_MACHINE;
		}
	}

	// ������ �� ����
	if (INPUT->IsKeyDown(VK_4))
	{		
		item_state = ITEM_LASERGUN;
		if (m_itemBag.find(1004) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1004];
			ani_state = IDLE_LASER;
		}
	}

	//����ź ����
	if (INPUT->IsKeyDown(VK_Q))
	{
		//item_state = ITEM_GRENADE;
		if (gre_state == GRENADE_IDLE)	gre_state = GRENADE_NONE;
		else 							gre_state = GRENADE_IDLE;
	}

	//������ ����
	if (INPUT->IsKeyDown(VK_W))
	{
		//item_state = ITEM_AIRBOMB;
		if (gre_state == AIRBOMB_IDLE)	gre_state = GRENADE_NONE;
		else 							gre_state = AIRBOMB_IDLE;
	}

	//ȭ��ź ����
	if (INPUT->IsKeyDown(VK_E))
	{
		//item_state = ITEM_RAVAREGION;
		if (gre_state == FLAME_IDLE)	gre_state = GRENADE_NONE;
		else 							gre_state = FLAME_IDLE;
	}

	//ȭ��ź ����
	if (INPUT->IsKeyDown(VK_R))
	{
		//item_state = ITEM_BUNKERREPAIR;
		/*if (gre_state == FLAME_IDLE)	gre_state = GRENADE_NONE;
		else 							gre_state = FLAME_IDLE;*/
	}
}

void Player::SetIdleAnimation()
{
	// �� ��� �ִϸ��̼��� ������ ��������Ʈ�̸� �� ���� Idle���·� ������. �̰� ���ؼ� �ѽ�� ��������Ʈ ������ ���� 1�� �� �־����.
		switch (m_pItem->GetTag())
		{
		case ITEM_PISTOL:
			if(Animation()->Current()->GetCurrentIndex() == 3) ani_state = IDLE_PISTOL;
			break;
		case ITEM_SHOTGUN:
			if (Animation()->Current()->GetCurrentIndex() == 3) ani_state = IDLE_SHOT;
			break;
		case ITEM_MACHINEGUN:
			if (Animation()->Current()->GetCurrentIndex() == 7) ani_state = IDLE_MACHINE;
			break;
		case ITEM_LASERGUN:
			if (Animation()->Current()->GetCurrentIndex() == 21) ani_state = IDLE_LASER;
			break;
		}


}

void Player::SetShotAnimation()
{
	switch (m_pItem->GetTag())
	{
	case ITEM_PISTOL:
		ani_state = SHOT_PISTOL;
		break;
	case ITEM_SHOTGUN:
		ani_state = SHOT_SHOT;
		break;
	case ITEM_MACHINEGUN:
		ani_state = SHOT_MACHINE;
		break;
	case ITEM_LASERGUN:
		ani_state = SHOT_LASER;
		break;
	}
}

void Player::AddItem(Object* pItem)
{
	int selectedCount;
	switch (pItem->GetItemTypeTag())
	{
	case ITEMTYPE_WEAPON:
		if (m_itemBag.find(pItem->GetTag()) == m_itemBag.end())
		{
			m_itemBag[pItem->GetID()] = new Item(pItem->GetID());
		}
		break;

	case ITEMTYPE_BULLET:
		selectedCount = SCENE->GetScene(SCENE_SHOP)->GetInputCount();
		if (m_itemBag.find(pItem->GetTag()) == m_itemBag.end())
		{
			m_itemBag[pItem->GetID()] = new Item(pItem->GetID());
			m_itemBag[pItem->GetID()]->AddCurrentCount(selectedCount);
		}
		if (m_itemBag.find(pItem->GetTag()) != m_itemBag.end())
		{
			m_itemBag[pItem->GetID()]->AddCurrentCount(selectedCount);
		}
		break;

	case ITEMTYPE_USINGITEM:
		selectedCount = SCENE->GetScene(SCENE_SHOP)->GetInputCount();
		if (m_itemBag.find(pItem->GetTag()) == m_itemBag.end())
		{
			if (selectedCount == 1)	m_itemBag[pItem->GetID()] = new Item(pItem->GetID());
			else if (selectedCount > 1)
			{
				m_itemBag[pItem->GetID()] = new Item(pItem->GetID());
				pItem->AddCurrentCount(selectedCount - 1);
			}
		}
		if (m_itemBag.find(pItem->GetTag()) != m_itemBag.end())
		{
			pItem->AddCurrentCount(selectedCount);
		}
		break;

	}
}