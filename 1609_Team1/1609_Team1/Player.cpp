#include "Player.h"



Player::Player()
{
}

Player::Player(OBJ_TAG tag) : Object(tag)
{
	// 총기 사운드
	SOUND->LoadFile("PistolShot", "Sound/Gun/Pistol.mp3", false);
	SOUND->LoadFile("ShotGunShot", "Sound/Gun/ShotGun.mp3", false);
	SOUND->LoadFile("MachineGunShot", "Sound/Gun/MachineGun.mp3", false);
	SOUND->LoadFile("LaserGunCharging", "Sound/Gun/LaserGunCharging.mp3", false);
	SOUND->LoadFile("LaserGunShot", "Sound/Gun/LaserGunShot.mp3", false);

	ani_state = IDLE_PISTOL;
	m_greCoolTime = 0.0f;//수류탄 쿨타임
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

	Object* startGrenade = OBJECT->CreateItem(ITEM_GRENADE, 3001);
	m_itemBag[startGrenade->GetTag()] = startGrenade;
	startBullet->AddCurrentCount(1);

	

	m_money = 10000;
	m_score = 0;

	gre_state = GRENADE_NONE;

	m_lagerChargerTime = 0;
	// 레이저건 충전 나타낼 바
	m_lasergunCharger = new UIProgressBar(Vector(VIEW_WIDTH*0.5 - 90, VIEW_HEIGHT - 15), Vector(240, 30), ColorF::Green, ColorF::Gray);
	m_lasergunCharger->SetMinMaxColor(ColorF::Red, ColorF::Green);
	m_lasergunCharger->SetValue(0.0f);
	m_laserGunShot = false;

	//전체 탄수
	All_Bullet_Pistol = 50;
	All_Bullet_Shot = 0;
	All_Bullet_Laser = 0;
	All_Bullet_Machine = 0;

	//장전 돼있던 탄수
	In_Bullet_Pistol = 0;
	In_Bullet_Shot=0;
	In_Bullet_Laser=0;
	In_Bullet_Machine=0;

	Count_Grenade=1;
	Count_Radio=0;
	Count_Napalm=0;
	Count_Repair=0;

	InBulletCount = 10;
	MaxBulletCount = 10;
	AllBulletCount = All_Bullet_Pistol;
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
		pos = Vector(VIEW_WIDTH / 2 + 30, VIEW_HEIGHT - 15);
		break;
	}
	return pos;
}

void Player::AttackState(float deltaTime)
{
	SetIdleAnimation();				// 총의 Shot 애니메이션 끝나면 그 총의 Idle 애니메이션으로 돌리는 함수
	Animation()->Play(ani_state);	// 현재 아이템에 대한 애니메이션 재생
	LaserChargerUpdate(deltaTime);	// 레이저건 충전 막대 업데이트
	
	CheckBullet();
	
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
	if (INPUT->IsKeyDown(VK_F6))
	{
		SCENE->SetColliderOnOff();
	}

	//좌클릭시 발사 부분 ( Down ) 
	if (INPUT->IsMouseDown(MOUSE_LEFT)) {
		if (InBulletCount > 0) {
			if (gre_state != GRENADE_NONE) {
				if (m_greCoolTime == 0.0f) {
					BulletUse(gre_state);
					Vector pos = MATH->ToDirection(90) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
					OBJECT->CreateGrenade(OBJ_GRENADE, pos, gre_state);
					m_greCoolTime = 2.0f;
				}
			}
			else {
				SetShotSound();
				SetShotAnimation();
				if (m_pItem->GetTag() != ITEM_LASERGUN)	//	레이저건은 3초 Press하고 쏘기 때문에 press쪽에 bullet 생성하는 거 넣어둠
				{
					BulletUse(m_pItem->GetTag());
					float sightHeightDefault = SIGHTHEIGHT_DEFAULT;
					float rate = 1 + MATH->Clamp(OBJECT->GetSightHeight() - sightHeightDefault, sightHeightDefault / 2 * -1, 0.0f) / sightHeightDefault;
					Vector pos = Vector::Up() * m_pItem->GetRange() * rate + OBJECT->GetPlayer()->Position();
					OBJECT->CreateBullet(OBJ_BULLET, pos, m_pItem->GetTag());
				}
			}
		}
	}

	// 좌클릭 후 Press
	if (INPUT->IsMousePress(MOUSE_LEFT))
	{
		if (m_pItem->GetTag() == ITEM_LASERGUN)		// 레이저건은 Press로 충전을 해야된다고 하여 예외처리함 ( Press이면 레이저 충전 3초하고, 그거 지나면 레이저 발사하도록)
		{
			SetShotSound();
			m_lagerChargerTime = MATH->Clamp(m_lagerChargerTime + deltaTime, 0.0f, 3.0f);

			if (Animation()->Current()->GetCurrentIndex() == 15
				&& !m_laserGunShot)
			{
				SOUND->Stop("LasergunCharging");
				SOUND->Play("LasergunShot", 1.0f);
				float sightHeightDefault = SIGHTHEIGHT_DEFAULT;
				float rate = 1 + MATH->Clamp(OBJECT->GetSightHeight() - sightHeightDefault, sightHeightDefault / 2 * -1, 0.0f) / sightHeightDefault;
				Vector pos = Vector::Up() * m_pItem->GetRange() * rate + OBJECT->GetPlayer()->Position();
				OBJECT->CreateBullet(OBJ_BULLET, pos, m_pItem->GetTag());
				m_laserGunShot = true;
			}
		}
	}

	// 좌클릭 후 Up
	if (INPUT->IsMouseUp(MOUSE_LEFT))
	{
		if (m_pItem->GetTag() == ITEM_LASERGUN)		// 레이저건은 Press로 충전을 해야된다고 하여 예외처리함
		{
			m_lagerChargerTime = 0.0f;
			ani_state = IDLE_LASER;
			m_laserGunShot = false;
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

void  Player::BulletReload() {
	if (AllBulletCount > 0) {
		if (AllBulletCount >= MaxBulletCount) {
			AllBulletCount -= (MaxBulletCount - InBulletCount);
			InBulletCount = MaxBulletCount;
		}
		else {
			if (AllBulletCount + InBulletCount >= MaxBulletCount) {
				AllBulletCount = AllBulletCount + InBulletCount - MaxBulletCount;
				InBulletCount = MaxBulletCount;
			}
			else {
				InBulletCount += AllBulletCount;
				AllBulletCount = 0;
			}
			
		}
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
	if (INPUT->IsKeyDown(VK_F6))
	{
		SCENE->SetColliderOnOff();
	}

	map<int, Object*> check;

	// 마우스 왼쪽 버튼 클릭
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
					SCENE->GetScene(SCENE_SHOP)->InputCountClear();
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
					SCENE->GetScene(SCENE_SHOP)->InputCountClear();
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
					SCENE->GetScene(SCENE_SHOP)->InputCountClear();
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
					SCENE->GetScene(SCENE_SHOP)->InputCountClear();
					break;

				case BUTTON_COUNT:		// 수량 버튼 선택시 숫자 입력칸 활성화
					if (SCENE->GetScene(SCENE_SHOP)->GetIsCountClicked() == true)
					{
						SCENE->GetScene(SCENE_SHOP)->SetInputOnOff(true);
					}
					break;

				case BUTTON_BUY:		// 샵씬에서 구매 선택하면 그 아이템이 아이템 가방에 저장됨
					if (SCENE->GetScene(SCENE_SHOP)->GetInputCount() != 0)
					{
						pItem = SCENE->GetScene(SCENE_SHOP)->GetSelectedItem();
						int	pItemMoney = pItem->GetItemMoney() * SCENE->GetScene(SCENE_SHOP)->GetInputCount();

						if (OBJECT->GetPlayer()->GetMoney() >= pItemMoney)
						{
							AddItem(pItem);
							OBJECT->GetPlayer()->AddMoney(-pItemMoney);
							SCENE->GetScene(SCENE_SHOP)->InputCountClear();
						}
					}
					break;				

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
		if (INPUT->IsKeyDown(VK_1))	num = 1;
		if (INPUT->IsKeyDown(VK_2)) num = 2;
		if (INPUT->IsKeyDown(VK_3)) num = 3;
		if (INPUT->IsKeyDown(VK_4)) num = 4;
		if (INPUT->IsKeyDown(VK_5)) num = 5;
		if (INPUT->IsKeyDown(VK_6)) num = 6;
		if (INPUT->IsKeyDown(VK_7)) num = 7;
		if (INPUT->IsKeyDown(VK_8)) num = 8;
		if (INPUT->IsKeyDown(VK_9)) num = 9;

		if (num != 0) SCENE->GetScene(SCENE_SHOP)->SetInputCount(num);
	}	// InputCount Bool함수 END
}

void Player::SetItem()
{
	// 권총 장착
	if (INPUT->IsKeyDown(VK_1))
	{
		if (m_itemBag.find(1001) != m_itemBag.end())
		{
			SaveBullet(item_state);
			InBulletCount = In_Bullet_Pistol;
			AllBulletCount = All_Bullet_Pistol;
			MaxBulletCount = 10;
			m_pItem = m_itemBag[1001];
			item_state = ITEM_PISTOL;
			ani_state = IDLE_PISTOL;
		}
	}

	// 샷건 장착
	if (INPUT->IsKeyDown(VK_2))
	{
		if (m_itemBag.find(1002) != m_itemBag.end())
		{
			SaveBullet(item_state);
			InBulletCount = In_Bullet_Shot;
			AllBulletCount = All_Bullet_Shot;
			MaxBulletCount = 2;
			m_pItem = m_itemBag[1002];
			item_state = ITEM_SHOTGUN;
			ani_state = IDLE_SHOT;
		}
	}

	// 기관총 장착
	if (INPUT->IsKeyDown(VK_3))
	{
		if (m_itemBag.find(1003) != m_itemBag.end())
		{
			SaveBullet(item_state);
			InBulletCount = In_Bullet_Machine;
			AllBulletCount = All_Bullet_Machine;
			MaxBulletCount = 500;
			m_pItem = m_itemBag[1003];
			item_state = ITEM_MACHINEGUN;
			ani_state = IDLE_MACHINE;
		}
	}

	// 레이저 건 장착
	if (INPUT->IsKeyDown(VK_4))
	{		
		if (m_itemBag.find(1004) != m_itemBag.end())
		{
			SaveBullet(item_state);
			InBulletCount = In_Bullet_Laser;
			AllBulletCount = All_Bullet_Laser;
			MaxBulletCount = 1000;
			m_pItem = m_itemBag[1004];
			item_state = ITEM_LASERGUN;
			ani_state = IDLE_LASER;
		}
	}

	//수류탄 장착
	if (INPUT->IsKeyDown(VK_Q))
	{
		if (m_itemBag.find(3001) != m_itemBag.end()) {
			SaveBullet(item_state);
			InBulletCount = Count_Grenade;
			MaxBulletCount = 0;
			AllBulletCount = 0;
			if (gre_state == GRENADE_IDLE)	gre_state = GRENADE_NONE;
			else 							gre_state = GRENADE_IDLE;
		}
	}

	//무전기 장착
	if (INPUT->IsKeyDown(VK_W))
	{
		if (m_itemBag.find(3002) != m_itemBag.end()) {
			SaveBullet(item_state);
			InBulletCount = Count_Radio;
			MaxBulletCount = 0;
			AllBulletCount = 0;
			if (gre_state == AIRBOMB_IDLE)	gre_state = GRENADE_NONE;
			else 							gre_state = AIRBOMB_IDLE;
		}
	}

	//화염탄 장착
	if (INPUT->IsKeyDown(VK_E))
	{
		if (m_itemBag.find(3003) != m_itemBag.end()) {
			SaveBullet(item_state);
			InBulletCount = Count_Napalm;
			MaxBulletCount = 0;
			AllBulletCount = 0;
			if (gre_state == FLAME_IDLE)	gre_state = GRENADE_NONE;
			else 							gre_state = FLAME_IDLE;
		}
	}

	//수리 장착
	if (INPUT->IsKeyDown(VK_R))
	{
		if (m_itemBag.find(3004) != m_itemBag.end()) {
			OBJECT->GetBunker()->AddCurrentLife(200);
			m_itemBag[ITEM_BUNKERREPAIR]->AddCurrentCount(-1);
			//item_state = ITEM_BUNKERREPAIR;
			/*if (gre_state == FLAME_IDLE)	gre_state = GRENADE_NONE;
			else 							gre_state = FLAME_IDLE;*/
		}
	}

	if (INPUT->IsKeyDown(VK_F))
	{
		BulletReload();
	}
}
void Player::SaveBullet(INT item_tag) {
	switch (item_tag) {
	case ITEM_PISTOL:
		All_Bullet_Pistol = AllBulletCount;
		In_Bullet_Pistol = InBulletCount;
		break;
	case ITEM_MACHINEGUN:
		All_Bullet_Machine = AllBulletCount;
		In_Bullet_Machine = InBulletCount;
		break;
	case ITEM_LASERGUN:
		All_Bullet_Laser = AllBulletCount;
		In_Bullet_Laser = InBulletCount;
		break;
	case ITEM_SHOTGUN:
		All_Bullet_Shot = AllBulletCount;
		In_Bullet_Shot = InBulletCount;
		break;
	case GRENADE_IDLE:
		Count_Grenade = InBulletCount;
		break;
	case AIRBOMB_IDLE:
		Count_Radio = InBulletCount;
		break;
	case FLAME_IDLE:
		Count_Napalm = InBulletCount;
		break;
	}
}
void Player::SetIdleAnimation()
{
	// 총 쏘는 애니메이션의 마지막 스프라이트이면 그 총의 Idle상태로 돌리기. 이거 위해서 총쏘는 스프라이트 마지막 장은 1장 더 넣어놓음.
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

void Player::SetShotSound()
{
	switch (m_pItem->GetTag())
	{
	case ITEM_PISTOL:
		SOUND->Play("PistolShot", 1.0f);
		break;

	case ITEM_SHOTGUN:
		SOUND->Play("ShotGunShot", 1.0f);
		break;

	case ITEM_MACHINEGUN:
		SOUND->Play("MachineGunShot", 1.0f);
		break;

	case ITEM_LASERGUN:
		SOUND->Play("LaserGunCharging", 1.0f);
		break;
	}
}

void Player::LaserChargerUpdate(float deltaTime)
{
	if (m_pItem->GetTag() == ITEM_LASERGUN)
	{
		if (Animation()->Current()->GetCurrentIndex() == 21)
		{
			m_lagerChargerTime = 0.0f;
			m_lasergunCharger->SetValue(0.0f);
		}
		m_lasergunCharger->SetTargetValue(m_lagerChargerTime / 3.0f);
		m_lasergunCharger->Update(deltaTime);
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

void Player::CheckBullet() {
	if (gre_state == GRENADE_NONE) {
		switch (item_state) {
		case ITEM_PISTOL:
			AllBulletCount = m_itemBag[ITEM_PSBULLET]->GetCurrentCount() - InBulletCount;
			break;
		case ITEM_MACHINEGUN:
			AllBulletCount = m_itemBag[ITEM_MGBULLET]->GetCurrentCount() - InBulletCount;
			break;
		case ITEM_LASERGUN:
			AllBulletCount = m_itemBag[ITEM_LGBULLET]->GetCurrentCount() - InBulletCount;
			break;
		case ITEM_SHOTGUN:
			AllBulletCount = m_itemBag[ITEM_SGBULLET]->GetCurrentCount() - InBulletCount;
			break;
		}
	}
	else {
		switch (gre_state) {
		case GRENADE_IDLE:
			AllBulletCount = m_itemBag[ITEM_GRENADE]->GetCurrentCount() - InBulletCount;
			break;
		case AIRBOMB_IDLE:
			AllBulletCount = m_itemBag[ITEM_AIRBOMB]->GetCurrentCount() - InBulletCount;
			break;
		case FLAME_IDLE:
			AllBulletCount = m_itemBag[ITEM_FIRECAPSULE]->GetCurrentCount() - InBulletCount;
			break;
		}
	}
	
}

void Player::BulletUse(INT item_tag) {
	InBulletCount -= 1;
	//INT BulletCount=AllBulletCount + InBulletCount;
	
	switch (item_tag) {
	case ITEM_PISTOL:
		m_itemBag[ITEM_PSBULLET]->AddCurrentCount(-1);
		break;
	case ITEM_MACHINEGUN:
		m_itemBag[ITEM_MGBULLET]->AddCurrentCount(-1);
		break;
	case ITEM_LASERGUN:
		m_itemBag[ITEM_LGBULLET]->AddCurrentCount(-1);
		break;
	case ITEM_SHOTGUN:
		m_itemBag[ITEM_SGBULLET]->AddCurrentCount(-1);
		break;
	case GRENADE_IDLE:
		m_itemBag[ITEM_GRENADE]->AddCurrentCount(-1);
		break;
	case AIRBOMB_IDLE:
		m_itemBag[ITEM_AIRBOMB]->AddCurrentCount(-1);
		break;
	case FLAME_IDLE:
		m_itemBag[ITEM_FIRECAPSULE]->AddCurrentCount(-1);
		break;
	}	
}