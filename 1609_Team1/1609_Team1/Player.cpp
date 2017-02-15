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


	// 씬 채인지
	if (INPUT->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene(SCENE_SHOP);
		m_state = PLAYER_SHOP;
	}

	//윈도우 종료
	if (INPUT->IsKeyDown(VK_F4))
	{
		PostQuitMessage(0);
	}

	// 총 장착 함수
	SetItem();

	// 충돌체 On/Off
	if (INPUT->IsKeyDown(VK_0))
	{
		SCENE->SetColliderOnOff();
	}

	//좌클릭시 발사 부분
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

	
	// 마우스 움직이면 모든 오브젝트들이 플레이어 중심으로 회전하는 처리 시작---------------------------------------------------
	// 커서 화면 밖으로 나가지 않도록 보정. 이게 앞으로 마우스 이전좌표와 현재좌표를 가지고 계산하는 부분의 앞에 있어야 함.
	if (m_prevMousePos.x <= 100
		|| m_prevMousePos.x >= 1000
		|| m_prevMousePos.y < 100
		|| m_prevMousePos.y> 800)
	{
		SetCursorPos(500, 500);
		m_prevMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	}
	
	// 이전 마우스좌표와 움직인 마우스 좌표를 비교하는 부분
	float fTurnSpeed = 0;
	float deltaHeight = 0;
	Vector NowMousePos = Vector(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	Vector gap = m_prevMousePos - NowMousePos;

	// 마우스 우측으로 움직였을 때
	if (gap.x > 0) 
	{
		fTurnSpeed = ROTATE_SPEED * deltaTime * gap.x;
	}

	// 마우스 좌측으로 움직였을 때
	if (gap.x < 0) 
	{
		fTurnSpeed = ROTATE_SPEED * deltaTime * gap.x;
	}

	// 마우스 위쪽으로 움직였을 때
	if (gap.y < 0) 
	{
		// 마우스에 의해 변화된 높이값 계산
		deltaHeight = ROTATE_SPEED * deltaTime * gap.y * 10;
	}

	// 마우스 아래쪽으로 움직였을 때
	if (gap.y > 0) 
	{
		// 마우스에 의해 변화된 높이값 계산
		deltaHeight = ROTATE_SPEED * deltaTime * gap.y * 10;
	}
	
	// 마우스 이동에 의한 변화값들을 오브젝트 메니저에 셋팅해주기. SetDeltaSightAngle는 미니맵에서 크리쳐 회전을 위해 사용됨. 
	OBJECT->SetDeltaSightAngle(fTurnSpeed * -1);
	OBJECT->SetDeltaSightHeight(deltaHeight * -1);

	// 플레이어가 보는 높이값 증감시켜주는 부분
	OBJECT->SetSightHeight(deltaHeight);	

	// m_prevMousePos를 현재 커서 위치로 초기화
	m_prevMousePos = NowMousePos;


	// 마우스 움직이면 모든 오브젝트들이 플레이어 중심으로 회전하는 처리 끝---------------------------------------------------

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
	if (INPUT->IsKeyDown(VK_0))
	{
		SCENE->SetColliderOnOff();
	}

	// 마우스 왼쪽 버튼 클릭
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

				case BUTTON_COUNT:		// 수량 버튼 선택시 숫자 입력칸 활성화
					SCENE->GetScene(SCENE_SHOP)->SetInputOnOff(true);
					break;

				case BUTTON_BUY:		// 샵씬에서 구매 선택하면 그 아이템이 아이템 가방에 저장됨
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
	}	// switch문 END

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

	}	// InputCount Bool함수 END
}

void Player::SetItem()
{
	// 권총 장착
	if (INPUT->IsKeyDown(VK_1))
	{
		item_state = ITEM_PISTOL;
		if (m_itemBag.find(1001) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1001];
		}
	}

	// 기관총 장착
	if (INPUT->IsKeyDown(VK_2))
	{
		item_state = ITEM_MACHINEGUN;
		if (m_itemBag.find(1002) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1002];
		}
	}

	// 화염 방사기 장착
	if (INPUT->IsKeyDown(VK_3))
	{
		if (m_itemBag.find(1003) != m_itemBag.end())
		{
			m_pItem = m_itemBag[1003];
		}
	}

	// 레이저 건 장착
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