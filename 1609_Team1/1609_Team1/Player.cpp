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


	//적들
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

	// 충돌체 On/Off
	if (INPUT->IsKeyDown(VK_0))
	{
		SCENE->SetColliderOnOff();
	}

	// 마우스 움직이면 모든 오브젝트들이 플레이어 중심으로 회전하는 처리 시작---------------------------------------------------
	// 이전 마우스좌표와 움직인 마우스 좌표를 비교하는 부분
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

	// 크리쳐 리스트 불러다가 미니맵 상의 pos 수정해주는 부분
	list<Object*> creatureList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, creatureList)
	{
		float angle = MATH->Angle(Vector::Right(), (*it)->GetMoveDirection() * -1);
		angle += fTurnSpeed;

		// 점 p(0,0)를 기준으로 구해진 새로운 pos를 플레이어 위지 p'(MINI_WIDTH * 0.5, MINI_HEIGHT) 기준으로 (*it)의 좌표 보정
		float x = MINI_WIDTH*0.5f + MATH->Cos(angle) * MINI_WIDTH * 0.5f;
		float y = MINI_HEIGHT +  MATH->Sin(angle) * MINI_WIDTH * 0.5f;

		(*it)->SetStartPos(Vector(x, y));
	}
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
				case 8:// 샵씬에서 구매 선택하면 그 아이템이 아이템 가방에 저장됨
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