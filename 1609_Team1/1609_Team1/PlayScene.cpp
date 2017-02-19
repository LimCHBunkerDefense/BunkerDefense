#include "PlayScene.h"



PlayScene::PlayScene() : m_attackedColor(ColorF::Red)
{
	// 크리쳐 생성되는 높이h값 생성. 추후 마우스에 따라 실시간 변화
	//m_heightOfCreature = 600;

	//캐릭터 나타내는 이미지
	RENDER->LoadImageFiles(TEXT("Idle_Pistol"), TEXT("Image/Item/Pistol/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("Attack_Pistol"), TEXT("Image/Item/Pistol/Attack/Attack"), TEXT("png"), 4);
	RENDER->LoadImageFiles(TEXT("Idle_Machine"), TEXT("Image/Item/MachineGun/Idle/MachineGunIdle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("Attack_Machine"), TEXT("Image/Item/MachineGun/Shot/MachineGunShot"), TEXT("png"), 8);
	RENDER->LoadImageFiles(TEXT("Idle_Laser"), TEXT("Image/Item/LaserGun/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("Attack_Laser"), TEXT("Image/Item/LaserGun/Shot/Shot"), TEXT("png"), 22);
	RENDER->LoadImageFiles(TEXT("Idle_Shot"), TEXT("Image/Item/ShotGun/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("Attack_Shot"), TEXT("Image/Item/ShotGun/Shot/Shot"), TEXT("png"), 4);
	RENDER->LoadImageFiles(TEXT("Reload_Shot"), TEXT("Image/Item/ShotGun/Reload/Reload"), TEXT("png"), 11);

	// 배경 이미지 맵으로 저장
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); 
	RENDER->LoadImageFile(TEXT("DroughtBG"), TEXT("Image/BackGround/DroughtBG.png"));

	// UI 이미지 맵으로 저장
	RENDER->LoadImageFile(TEXT("Aim"), TEXT("Image/UI/Aim/Aim.png"));
	//RENDER->LoadImageFile(TEXT("Minimap"), TEXT("Image/UI/Minimap/Minimap.png"));
	RENDER->LoadImageFile(TEXT("Radar"), TEXT("Image/UI/Minimap/RadarBG.png"));
	
	// 크리처 이미지 생성
	// Ent
	RENDER->LoadImageFiles(TEXT("EntIdle"), TEXT("Image/Creature/Ent/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 21);	
	RENDER->LoadImageFiles(TEXT("EntAttack"), TEXT("Image/Creature/Ent/Attack/Attack"), TEXT("png"), 16);
	RENDER->LoadImageFiles(TEXT("EntDie"), TEXT("Image/Creature/Ent/Die/Die"), TEXT("png"), 7);
	// Lava
	RENDER->LoadImageFiles(TEXT("LavaIdle"), TEXT("Image/Creature/Lava/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("LavaRun"), TEXT("Image/Creature/Lava/Run/Run"), TEXT("png"), 23);
	RENDER->LoadImageFiles(TEXT("LavaAttack"), TEXT("Image/Creature/Lava/Attack/Attack"), TEXT("png"), 21);
	RENDER->LoadImageFiles(TEXT("LavaDie"), TEXT("Image/Creature/Lava/Die/Die"), TEXT("png"), 13);
	// DarkPriest
	RENDER->LoadImageFiles(TEXT("DarkpriestIdle"), TEXT("Image/Creature/DarkPriest/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("DarkpriestRun"), TEXT("Image/Creature/DarkPriest/Walk/Walk"), TEXT("png"), 16);
	RENDER->LoadImageFiles(TEXT("DarkpriestAttack"), TEXT("Image/Creature/DarkPriest/Attack/Attack"), TEXT("png"), 32);
	RENDER->LoadImageFiles(TEXT("DarkpriestDie"), TEXT("Image/Creature/DarkPriest/Die/Die"), TEXT("png"), 23);

	//인터페이스 UI 이미지 가져오기
	RENDER->LoadImageFile(TEXT("StageFont_UI"), TEXT("Image/UI/InterfaceUI/stage.png"));
	RENDER->LoadImageFile(TEXT("ItemBar_UI"), TEXT("Image/UI/InterfaceUI/ItemBarUI.png"));
	RENDER->LoadImageFile(TEXT("Bunker_UI"), TEXT("Image/UI/InterfaceUI/Bunker_UI.png"));
	RENDER->LoadImageFile(TEXT("ScoreUI"), TEXT("Image/UI/InterfaceUI/Score.png"));
	RENDER->LoadImageFile(TEXT("MoneyUI"), TEXT("Image/UI/InterfaceUI/money.png"));

	//Bullet 저장
	RENDER->LoadImageFiles(TEXT("PSBulletIdle"), TEXT("Image/Bullet/Pistol/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("PSBulletExplode"), TEXT("Image/Bullet/Pistol/Explode/Explode"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("MGBulletIdle"), TEXT("Image/Bullet/Machinegun/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("MGBulletExplode"), TEXT("Image/Bullet/Machinegun/Explode/Explode"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("SGBulletIdle"), TEXT("Image/Bullet/Shotgun/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("SGBulletExplode"), TEXT("Image/Bullet/Shotgun/Explode/Explode"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("LGBulletIdle"), TEXT("Image/Bullet/Lasergun/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("LGBulletExplode"), TEXT("Image/Bullet/Lasergun/Explode/Explode"), TEXT("png"), 1);

	//Grenade 저장
	RENDER->LoadImageFiles(TEXT("Grenade"), TEXT("Image/Item/Grenade/Grenade"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Explode"), TEXT("Image/Item/Explode/explode"), TEXT("png"), 7);
	RENDER->LoadImageFiles(TEXT("Flame_idle"), TEXT("Image/Item/Grenade/Napalm"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Flame_Explode"), TEXT("Image/Item/Flame/flame"), TEXT("png"), 30);
	RENDER->LoadImageFiles(TEXT("Plane_idle"), TEXT("Image/Item/Grenade/AirPlane"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Plane_Explode"), TEXT("Image/Item/SkyBomb/airBomb"), TEXT("png"), 42);

	//무기 ICON 가져오기
	RENDER->LoadImageFile(TEXT("PistolOn"),		TEXT("Image/Item/Icon/ico_pistol_on.png"));
	RENDER->LoadImageFile(TEXT("PistolOff"),	TEXT("Image/Item/Icon/ico_pistol_off.png"));
	RENDER->LoadImageFile(TEXT("ShotGunOn"), TEXT("Image/Item/Icon/ico_shot_on.png"));
	RENDER->LoadImageFile(TEXT("ShotGunOff"), TEXT("Image/Item/Icon/ico_shot_off.png"));
	RENDER->LoadImageFile(TEXT("MachineGunOn"), TEXT("Image/Item/Icon/ico_machine_on.png"));
	RENDER->LoadImageFile(TEXT("MachineGunOff"), TEXT("Image/Item/Icon/ico_machine_off.png"));
	RENDER->LoadImageFile(TEXT("LaserGunOn"),		TEXT("Image/Item/Icon/ico_laser_on.png"));
	RENDER->LoadImageFile(TEXT("LaserGunOff"),		TEXT("Image/Item/Icon/ico_laser_off.png"));
	RENDER->LoadImageFile(TEXT("FixOn"), TEXT("Image/Item/Icon/ico_fix_on.png"));
	RENDER->LoadImageFile(TEXT("FixOff"), TEXT("Image/Item/Icon/ico_fix_off.png"));
	RENDER->LoadImageFile(TEXT("GrenadeOn"), TEXT("Image/Item/Icon/ico_grenade_on.png"));
	RENDER->LoadImageFile(TEXT("GrenadeOff"), TEXT("Image/Item/Icon/ico_grenade_off.png"));
	RENDER->LoadImageFile(TEXT("PlaneOn"), TEXT("Image/Item/Icon/ico_plane_on.png"));
	RENDER->LoadImageFile(TEXT("PlaneOff"), TEXT("Image/Item/Icon/ico_plane_off.png"));
	RENDER->LoadImageFile(TEXT("NapalmOn"), TEXT("Image/Item/Icon/ico_capsule_on.png"));
	RENDER->LoadImageFile(TEXT("NapalmOff"), TEXT("Image/Item/Icon/ico_capsule_off.png"));

	// 숫자 이미지 가져오기
	RENDER->LoadImageFile(TEXT("Num0"), TEXT("Image/UI/ScoreNUM/Num0.png"));
	RENDER->LoadImageFile(TEXT("Num1"), TEXT("Image/UI/ScoreNUM/Num1.png"));
	RENDER->LoadImageFile(TEXT("Num2"), TEXT("Image/UI/ScoreNUM/Num2.png"));
	RENDER->LoadImageFile(TEXT("Num3"), TEXT("Image/UI/ScoreNUM/Num3.png"));
	RENDER->LoadImageFile(TEXT("Num4"), TEXT("Image/UI/ScoreNUM/Num4.png"));
	RENDER->LoadImageFile(TEXT("Num5"), TEXT("Image/UI/ScoreNUM/Num5.png"));
	RENDER->LoadImageFile(TEXT("Num6"), TEXT("Image/UI/ScoreNUM/Num6.png"));
	RENDER->LoadImageFile(TEXT("Num7"), TEXT("Image/UI/ScoreNUM/Num7.png"));
	RENDER->LoadImageFile(TEXT("Num8"), TEXT("Image/UI/ScoreNUM/Num8.png"));
	RENDER->LoadImageFile(TEXT("Num9"), TEXT("Image/UI/ScoreNUM/Num9.png"));

	// BGM 사운드
	SOUND->LoadFile("MainBGM_0", "Sound/BGM/Main/Main_0.mp3", true);
	SOUND->LoadFile("MainBGM_1", "Sound/BGM/Main/Main_1.mp3", true);
	SOUND->LoadFile("MainBGM_2", "Sound/BGM/Main/Main_2.mp3", true);
	SOUND->LoadFile("ShopBGM_0", "Sound/BGM/Shop/Shop_0.mp3", true);


	// 벙커 체력 막대 생성
	m_bunkerLife = new UIProgressBar(Vector(24, 830), Vector(320, 45), ColorF::YellowGreen, ColorF::LightGoldenrodYellow);
	m_bunkerLife->SetMinMaxColor(ColorF::Red, ColorF::YellowGreen);

	// 총알 게이지 막대 생성
	m_bulletGage = new UIBulletBar(Vector(24, 770), Vector(320, 45), ColorF::DarkBlue, ColorF::LightBlue);

	// 카메라 생성
	RENDER->CreateCamera(CAM_MAIN, MAP_WIDTH, MAP_HEIGHT, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->CreateCamera(CAM_MINIMAP, MINI_WIDTH, MINI_HEIGHT* 5, MINI_WIDTH, MINI_HEIGHT * 2);
	RENDER->CreateCamera(CAM_UI, VIEW_WIDTH, VIEW_HEIGHT, VIEW_WIDTH, VIEW_HEIGHT);

	pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMinimapCamera = RENDER->GetCamera(CAM_MINIMAP);
	pUICamera = RENDER->GetCamera(CAM_UI);

	// 크리쳐 공격에 의한 흔들림 구현을 위해서 초기화
	m_MainCameraPos = Vector(0, 0);
	m_swayPos = Vector(300, 0);

	// 플레이어 생성
	OBJECT->CreatePlayer(Vector(MINI_WIDTH * 0.5F, MINI_HEIGHT), Vector(10, 10), Vector(0.5f, 1.0f));
	Object* p = OBJECT->GetPlayer();
	// 벙커 생성
	OBJECT->CreateBunker();
	Object* pObj = OBJECT->GetBunker();

	m_createdLavaCount = 0;
	m_createdEntCount = 0;
	m_createdDarkpriestCount = 0;
}


PlayScene::~PlayScene()
{
}


void PlayScene::OnEnter()
{
	// 배경 이미지 스프라이트로 생성
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("DroughtBG")), 1.8));

	// UI 이미지 스프라이트로 생성
	NEW_OBJECT(m_pAim, Sprite(RENDER->GetImage(TEXT("Aim")), 0.825));
	//NEW_OBJECT(m_pMinimap, Sprite(RENDER->GetImage(TEXT("Minimap")), 1.0));
	NEW_OBJECT(m_pRadar, Sprite(RENDER->GetImage(TEXT("Radar")), 0.85, 0.0,0.0));

	// UI 이미지 생성
	NEW_OBJECT(m_stageUI, Sprite(RENDER->GetImage(TEXT("StageFont_UI"))));
	NEW_OBJECT(m_ScoreUI, Sprite(RENDER->GetImage(TEXT("ScoreUI")),0.8f));
	NEW_OBJECT(m_MoneyUI, Sprite(RENDER->GetImage(TEXT("MoneyUI")), 0.8f));
	NEW_OBJECT(m_BunkerUI, Sprite(RENDER->GetImage(TEXT("Bunker_UI"))));
	NEW_OBJECT(m_ItemBarUI, Sprite(RENDER->GetImage(TEXT("ItemBar_UI"))));

	// PlayScene BGM 생성
	SOUND->Play("MainBGM_0", 1.0f);			// 후보군 1
	// SOUND->Play("MainBGM_1", 0.5f);		// 후보군 2
	// SOUND->Play("MainBGM_2", 0.5f);		// 후보군 3

	//ico pistol
	NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
	NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff"))));
	NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff"))));	
	NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff"))));

	NEW_OBJECT(m_ico_grenade, Sprite(RENDER->GetImage(TEXT("GrenadeOff"))));
	NEW_OBJECT(m_ico_plane, Sprite(RENDER->GetImage(TEXT("PlaneOff"))));
	NEW_OBJECT(m_ico_napalm, Sprite(RENDER->GetImage(TEXT("NapalmOff"))));
	NEW_OBJECT(m_ico_fix, Sprite(RENDER->GetImage(TEXT("FixOn"))));

	NEW_OBJECT(m_num1, Sprite(RENDER->GetImage(TEXT("Num1")), 1.0, 0,0));
	NEW_OBJECT(m_num2, Sprite(RENDER->GetImage(TEXT("Num2")), 1.0, 0,0));
	NEW_OBJECT(m_num3, Sprite(RENDER->GetImage(TEXT("Num3")), 1.0, 0,0));
	NEW_OBJECT(m_num4, Sprite(RENDER->GetImage(TEXT("Num4")), 1.0, 0,0));
	NEW_OBJECT(m_num5, Sprite(RENDER->GetImage(TEXT("Num5")), 1.0, 0,0));
	NEW_OBJECT(m_num6, Sprite(RENDER->GetImage(TEXT("Num6")), 1.0, 0,0));
	NEW_OBJECT(m_num7, Sprite(RENDER->GetImage(TEXT("Num7")), 1.0, 0,0));
	NEW_OBJECT(m_num8, Sprite(RENDER->GetImage(TEXT("Num8")), 1.0, 0,0));
	NEW_OBJECT(m_num9, Sprite(RENDER->GetImage(TEXT("Num9")), 1.0, 0,0));
	NEW_OBJECT(m_num0, Sprite(RENDER->GetImage(TEXT("Num0")), 1.0, 0,0));

	// 크리쳐 공격 연출을 위한 도구(색 저장용) 투명도 초기화
	m_attackedColor.a = 0;

	// 카메라 세팅
	pMainCamera->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
	pMinimapCamera->SetScreenRect(VIEW_WIDTH - MINI_WIDTH - 10, VIEW_HEIGHT - MINI_HEIGHT * 2 + 50, MINI_WIDTH, MINI_HEIGHT * 2);
	pUICamera->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);

	// 테스트용 크리쳐 생성
	OBJECT->CreateCreature(OBJ_ENT, Vector(120, 60));
	//OBJECT->CreateCreature(OBJ_LAVA, Vector(0, 180));
	//OBJECT->CreateCreature(OBJ_DARKPRIEST, Vector(120, 240));

	// 마우스 커서 없애기
	ShowCursor(false);

}

void PlayScene::OnUpdate(float deltaTime)
{
	//Icon 변경
	ChangeIcon();
	// 크리쳐 생성을 위한 게임 시간 업데이트
	m_gameTime += deltaTime;

	// 게임 시간에 따른 크리쳐 생성  
	//SetCreature(deltaTime);
	
	// 오브젝트 전체 업데이트
	OBJECT->Update(deltaTime);

	// 벙커 체력 UIProgressBar 업데이트(이것은 벙커 객체 소유물이 아닌 UI이므로 플레이씬에서 가지고 업데이트 하는 것이 맞아보임)
	m_bunkerLife->SetTargetValue(OBJECT->GetBunker()->GetCurrentLife() / OBJECT->GetBunker()->GetMaxLife());
	m_bunkerLife->Update(deltaTime);

	// m_attackedColor 투명도 조정하여 공격당함 연출 부분으로 투명도를 점점 높여주는 부분
	if (m_attackedColor.a != 0)
	{
		// 공격 당한 즉시 흔들림을 위한 카메라 위치 및 흔들림 변화량 초기화		
		if (m_attackedColor.a >= 0.4999)
		{
			pMainCamera->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
			m_MainCameraPos = Vector(0, 0);
		}

		// 흔들림 구현 함수
		SwayScreen(deltaTime);

		// 공격 표시를 위한 화면의 붉은색 표시부분의 투명도 감소
		m_attackedColor.a = MATH->Clamp(m_attackedColor.a - deltaTime, 0.0f, 20.0f);				
	}
	else if(m_attackedColor.a <= 0) pMainCamera->SetScreenRect(0,0, VIEW_WIDTH, VIEW_HEIGHT);

}

void PlayScene::ChangeIcon() {
	ITEM_TAG item_tag = OBJECT->GetPlayer()->GetItemState();
	GRENADE_STATE gre_state = OBJECT->GetPlayer()->GetGreState();
	if (item_tag == ITEM_PISTOL) {	NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));	}
	else { NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff")))); }
	if (item_tag == ITEM_SHOTGUN) { NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOn")))); }
	else { NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff")))); }
	if (item_tag == ITEM_MACHINEGUN) { NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOn")))); }
	else { NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff")))); }
	if (item_tag == ITEM_LASERGUN) { NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOn")))); }
	else { NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff")))); }

	if (gre_state == GRENADE_IDLE) { NEW_OBJECT(m_ico_grenade, Sprite(RENDER->GetImage(TEXT("GrenadeOn")))); }
	else { NEW_OBJECT(m_ico_grenade, Sprite(RENDER->GetImage(TEXT("GrenadeOff")))); }
	if (gre_state == AIRBOMB_IDLE) { NEW_OBJECT(m_ico_plane, Sprite(RENDER->GetImage(TEXT("PlaneOn")))); }
	else { NEW_OBJECT(m_ico_plane, Sprite(RENDER->GetImage(TEXT("PlaneOff")))); }
	if (gre_state == FLAME_IDLE) { NEW_OBJECT(m_ico_napalm, Sprite(RENDER->GetImage(TEXT("NapalmOn")))); }
	else { NEW_OBJECT(m_ico_napalm, Sprite(RENDER->GetImage(TEXT("NapalmOff")))); }
	NEW_OBJECT(m_ico_fix, Sprite(RENDER->GetImage(TEXT("FixOn"))));

	/*if (gre_state == GRENADE_IDLE) { NEW_OBJECT(m_ico_fix, Sprite(RENDER->GetImage(TEXT("PistolOn")))); }
	else { NEW_OBJECT(m_ico_fix, Sprite(RENDER->GetImage(TEXT("PistolOff")))); */


	/* Too Long
	switch (OBJECT->GetPlayer()->GetItemState()) {
		case ITEM_PISTOL: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
			NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff"))));
			NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff"))));
			NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff"))));
			break;
		}
		case ITEM_SHOTGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOn"))));
			NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff"))));
			NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff"))));
			break;
		}
		case ITEM_MACHINEGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff"))));
			NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOn"))));
			NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff"))));
			break;
		}
		case ITEM_LASERGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff"))));
			NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff"))));
			NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOn"))));
			break;
		}
	}*/
}

void PlayScene::OnExit()
{
	//Exit	

	// PlayScene 나갈 때 Pause 상태
	SOUND->Pause("MainBGM_0");			// 후보군 1
	// SOUND->Pause("MainBGM_1");		// 후보군 2
	// SOUND->Pause("MainBGM_2");		// 후보군 3
}

void PlayScene::OnDraw()
{	

	// 배경 그려주는 부분 (보이는 화면 좌우로 하나씩 더)
	DrawBG();

	// 임시 미니맵 배경
	pMinimapCamera->Draw(m_pRadar, Vector(-24, -23));

	// 미니맵 시야 각도 표시
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT,
		MINI_WIDTH * 0.5 - MINI_WIDTH * 0.5 * MATH->Sin(CAMERA_ANGLE * 0.5), MINI_HEIGHT - MINI_WIDTH * 0.5 * MATH->Cos(CAMERA_ANGLE * 0.5), ColorF::Yellow, 2);
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT,
		MINI_WIDTH * 0.5 + MINI_WIDTH * 0.5 * MATH->Sin(CAMERA_ANGLE * 0.5), MINI_HEIGHT - MINI_WIDTH * 0.5 * MATH->Cos(CAMERA_ANGLE * 0.5), ColorF::Yellow, 2);
	// pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT, MINI_WIDTH * 0.5, MINI_HEIGHT - MINI_WIDTH * 0.5, ColorF::Yellow, 1); 미니맵 레이더의 중앙선

	// 미니맵 크리쳐 생성되는 범위 표시	
	//pMinimapCamera->DrawCircle(Vector(MINI_WIDTH * 0.5, MINI_HEIGHT), Vector(MINI_WIDTH, MINI_WIDTH), ColorF::Yellow);

	// 미니맵에 플레이어 위치 표시
	pMinimapCamera->DrawFilledCircle(Vector(MINI_WIDTH * 0.5 , MINI_HEIGHT), Vector(8, 8), ColorF::Yellow);

	// 미니맵에 크리쳐 위치 표시
	list<Object*> pList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, pList)
	{
		Vector pos = (*it)->Position();
		Vector colSize = (*it)->Collider().size;
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::Red);
		pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::Red, 2);
		pMinimapCamera->DrawFilledRect(Vector(pos.x - colSize.x * 0.5, pos.y - colSize.y), colSize, ColorF::Blue);	// 미니맵 상 크리쳐의 충돌체 표시해주는 부분
	}

	//탄환 선 긋기
	list<Object*> pBulletList = OBJECT->GetBulletList();
	FOR_LIST(Object*, pBulletList)
	{
		Vector pos = (*it)->Position();
		Vector colSize = (*it)->Collider().size;
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::DeepPink);
		//pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::DeepPink, 2);
		//pMinimapCamera->DrawFilledRect(pos - colSize * 0.5, colSize, ColorF::Blue);	// 미니맵 상 총알의 충돌체 표시해주는 부분
	}

	//수류탄 선 긋기
	list<Object*> pGrenadeList = OBJECT->GetGrenadeList();
	FOR_LIST(Object*, pGrenadeList)
	{
		Vector pos = (*it)->Position();
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::Yellow);
		//pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::DeepPink, 2);
	}
	
	OBJECT->Draw(pMainCamera);

	// Aim 그려주는 부분
	pUICamera->Draw(m_pAim, Vector(VIEW_WIDTH * 0.5, VIEW_HEIGHT * 0.5f));

	//플레이 UI출력
	//1.Stage UI 출력
	pUICamera->Draw(m_stageUI, Vector(600, 100));
	pUICamera->DrawRect(Vector(565, 125), Vector(70, 70), ColorF::Red, 3);
	pUICamera->DrawT(TEXT("1"), 590, 140, ColorF::Red, 30, ALIGN_RIGHT);
	//pUICamera->DrawT(TEXT("Stage 1"), VIEW_WIDTH / 2 - 50, 40, ColorF::White, 30, ALIGN_CENTER);

	//2.벙커UI / 스킬 UI
	pUICamera->Draw(m_ItemBarUI, Vector(146, 80));
	pUICamera->Draw(m_BunkerUI, Vector(186, 820));
	
	//3.점수 출력
	//pUICamera->DrawT(TEXT("점수 : "), VIEW_WIDTH - 300, 30, ColorF::White, 30, ALIGN_RIGHT);
	//pUICamera->DrawT(TEXT("골드 : "), VIEW_WIDTH - 300, 70, ColorF::White, 30, ALIGN_RIGHT);
	pUICamera->Draw(m_ScoreUI, Vector(VIEW_WIDTH - 300, 45));
	ShowScore(pUICamera);
	pUICamera->Draw(m_MoneyUI, Vector(VIEW_WIDTH - 300, 100));
	ShowMoney(pUICamera);

	// 크리쳐에게 공격 받았음을 나타내기 위한 부분
	if (m_attackedColor.a != 0) pUICamera->DrawFilledRect(Vector(0,0), Vector(VIEW_WIDTH, VIEW_HEIGHT), m_attackedColor);

	//Bunker 체력
	m_bunkerLife->Render(pUICamera);

	// 총알 게이지
	m_bulletGage->Render(pUICamera);

	//Icon

	pUICamera->Draw(m_ico_pistol, Vector(48, VIEW_HEIGHT - 852));
	pUICamera->Draw(m_ico_shotGun, Vector(109, VIEW_HEIGHT - 852));
	pUICamera->Draw(m_ico_machineGun, Vector(172, VIEW_HEIGHT - 852));
	pUICamera->Draw(m_ico_laserGun, Vector(238, VIEW_HEIGHT - 852));

	pUICamera->Draw(m_ico_grenade, Vector(48, VIEW_HEIGHT - 792));
	pUICamera->Draw(m_ico_plane, Vector(109, VIEW_HEIGHT - 792));
	pUICamera->Draw(m_ico_napalm, Vector(172, VIEW_HEIGHT - 792));
	pUICamera->Draw(m_ico_fix, Vector(238, VIEW_HEIGHT - 792));
	//pUICamera->DrawRect(Vector(146, 85), Vector(50, 50), ColorF::Red, 1);

	
	pUICamera->DrawRect(Vector(24, VIEW_HEIGHT - 130), Vector(320, 45), ColorF::Blue, 2);
	//pUICamera->DrawRect(Vector(28, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red, 1);
	//pUICamera->DrawRect(Vector(118, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red, 1);
	//pUICamera->DrawRect(Vector(208, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red,1);
	//pUICamera->DrawRect(Vector(298, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red,1);

	// 레이저건 충전 막대 출력
	if (OBJECT->GetPlayer()->GetCurrentItem()->GetTag() == ITEM_LASERGUN)
	{
		OBJECT->GetPlayer()->GetLaserChargerBar()->Render(pUICamera);
	}
}

void PlayScene::SetCreature(float deltaTime)
{
	int randDegree;

	// 스테이지 1
	if(m_gameTime / 3 > m_createdLavaCount)
	{
		randDegree = rand() % 360;
		Vector pos = MATH->ToDirection(randDegree) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
		OBJECT->CreateCreature(OBJ_LAVA, pos);
		m_createdLavaCount++;
	}

	// 스테이지 2
	if ((m_gameTime -  20) / 5 > m_createdEntCount)
	{
		randDegree = rand() % 360;
		Vector pos = MATH->ToDirection(randDegree) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
		OBJECT->CreateCreature(OBJ_ENT, pos);
		m_createdEntCount++;
	}

	// 대빵
	if (m_gameTime>100 && m_createdDarkpriestCount < 1)
	{
		randDegree = rand() % 360;
		Vector pos = MATH->ToDirection(randDegree) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
		OBJECT->CreateCreature(OBJ_DARKPRIEST, pos);
		m_createdDarkpriestCount++;
	}

}

void PlayScene::DrawBG()
{
	Vector bgPos = OBJECT->GetSightPos();
	pMainCamera->Draw(m_pBg, bgPos);

	if(bgPos.x > 0) pMainCamera->Draw(m_pBg, bgPos - Vector(1920 * 2 * 1.8, 0));
	else pMainCamera->Draw(m_pBg, bgPos + Vector(1920 * 2 * 1.8, 0));
}

void PlayScene::SwayScreen(float deltaTime)
{
	if (m_MainCameraPos.x <= -10) m_swayPos *= -1;
	else if (m_MainCameraPos.x >= 10) m_swayPos *= -1;

	m_MainCameraPos += m_swayPos *deltaTime;

	pMainCamera->SetScreenRect(m_MainCameraPos.x, m_MainCameraPos.y, VIEW_WIDTH, VIEW_HEIGHT);
}

void PlayScene::ShowMoney(Camera* pCamera)
{
	int money = OBJECT->GetPlayer()->GetMoney();
	int num = 0;

	// 일의 자리
	num = money % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 40, 80));

	// 십의 자리
	num = money / 10 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 70, 80));

	// 백의 자리
	num = money / 100 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 100, 80));

	// 천의 자리
	num = money / 1000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 130, 80));

	// 만의 자리
	num = money / 10000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 160, 80));

	// 십만의 자리
	num = money / 100000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 190, 80));

	// 백만의 자리
	num = money / 1000000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 220, 80));
}

void PlayScene::ShowScore(Camera* pCamera)
{
	int score = OBJECT->GetPlayer()->GetScore();
	int num = 0;

	// 일의 자리
	num = score % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 40, 25));

	// 십의 자리
	num = score / 10 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 70, 25));

	// 백의 자리
	num = score / 100 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 100, 25));

	// 천의 자리
	num = score / 1000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 130, 25));

	// 만의 자리
	num = score / 10000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 160, 25));

	// 십만의 자리
	num = score / 100000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 190, 25));

	// 백만의 자리
	num = score / 1000000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 220, 25));
}

void PlayScene::DrawNum(Camera* pCamera, int num, Vector leftTop)
{
	switch (num)
	{
	case 0:
		pCamera->Draw(m_num0, leftTop, 1);
		break;
	case 1:
		pCamera->Draw(m_num1, leftTop, 1);
		break;
	case 2:
		pCamera->Draw(m_num2, leftTop, 1);
		break;
	case 3:
		pCamera->Draw(m_num3, leftTop, 1);
		break;
	case 4:
		pCamera->Draw(m_num4, leftTop, 1);
		break;
	case 5:
		pCamera->Draw(m_num5, leftTop, 1);
		break;
	case 6:
		pCamera->Draw(m_num6, leftTop, 1);
		break;
	case 7:
		pCamera->Draw(m_num7, leftTop, 1);
		break;
	case 8:
		pCamera->Draw(m_num8, leftTop, 1);
		break;
	case 9:
		pCamera->Draw(m_num9, leftTop, 1);
		break;
	}
}