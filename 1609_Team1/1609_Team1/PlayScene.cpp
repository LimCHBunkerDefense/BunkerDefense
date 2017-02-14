#include "PlayScene.h"



PlayScene::PlayScene()
{
	// 크리쳐 생성되는 높이h값 생성. 추후 마우스에 따라 실시간 변화
	m_heightOfCreature = 600;


	// 배경 이미지 맵으로 저장
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); 
	RENDER->LoadImageFile(TEXT("DroughtBG"), TEXT("Image/BackGround/DroughtBG.png"));

	// UI 이미지 맵으로 저장
	RENDER->LoadImageFile(TEXT("Aim"), TEXT("Image/UI/Aim/Aim.png"));
	RENDER->LoadImageFile(TEXT("Minimap"), TEXT("Image/UI/Minimap/Minimap.png"));
	RENDER->LoadImageFile(TEXT("Radar"), TEXT("Image/UI/Minimap/RadarBG.png"));

	// 크리쳐 데이터 생성
	CREATURE->Init();
	
	// 크리처 이미지 맵으로 저장
	RENDER->LoadImageFiles(TEXT("EntIdle"), TEXT("Image/Creature/Ent/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 9);
	RENDER->LoadImageFiles(TEXT("EntAttack"), TEXT("Image/Creature/Ent/Attack/Attack"), TEXT("png"), 6);

	//Bullet 임시로 저장
	RENDER->LoadImageFiles(TEXT("BulletIdle"), TEXT("Image/Bullet/bullet"), TEXT("png"), 1);

	//무기 ICON 가져오기
	RENDER->LoadImageFile(TEXT("PistolOn"),		TEXT("Image/Item/Icon/ico_pistol_on.png"));
	RENDER->LoadImageFile(TEXT("PistolOff"),	TEXT("Image/Item/Icon/ico_pistol_off.png"));
	RENDER->LoadImageFile(TEXT("LaserOn"),		TEXT("Image/Item/Icon/ico_laser_on.png"));
	RENDER->LoadImageFile(TEXT("LaserOff"),		TEXT("Image/Item/Icon/ico_laser_off.png"));
	RENDER->LoadImageFile(TEXT("MachineOn"),	TEXT("Image/Item/Icon/ico_machine_on.png"));
	RENDER->LoadImageFile(TEXT("MachineOff"),	TEXT("Image/Item/Icon/ico_machine_off.png"));


	// 카메라 생성
	RENDER->CreateCamera(CAM_MAIN, MAP_WIDTH, MAP_HEIGHT, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->CreateCamera(CAM_MINIMAP, MINI_WIDTH, MINI_HEIGHT* 2, MINI_WIDTH, MINI_HEIGHT * 2);
	RENDER->CreateCamera(CAM_UI, VIEW_WIDTH, VIEW_HEIGHT, VIEW_WIDTH, VIEW_HEIGHT);

	pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMinimapCamera = RENDER->GetCamera(CAM_MINIMAP);
	pUICamera = RENDER->GetCamera(CAM_UI);
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
	NEW_OBJECT(m_pMinimap, Sprite(RENDER->GetImage(TEXT("Minimap")), 1.0));
	NEW_OBJECT(m_pRadar, Sprite(RENDER->GetImage(TEXT("Radar")), 0.85, 0.0,0.0));

	//ico pistol
	NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
	NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOff"))));
	NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOff"))));	

	// 플레이어 생성
	OBJECT->CreatePlayer(Vector(MINI_WIDTH * 0.5F, MINI_HEIGHT), Vector(10, 10), Vector(0.5f, 1.0f));

	// 카메라 세팅
	RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->GetCamera(CAM_MINIMAP)->SetScreenRect(VIEW_WIDTH - MINI_WIDTH, VIEW_HEIGHT - MINI_HEIGHT * 2, MINI_WIDTH, MINI_HEIGHT * 2);
	RENDER->GetCamera(CAM_UI)->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);

	m_createdCretureCount = 0;

	// 테스트용 크리쳐 생성
	//OBJECT->CreateCreature(OBJ_ENT, Vector(120, 60));

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
	SetCreature(deltaTime);
	
	// 오브젝트 전체 업데이트
	OBJECT->Update(deltaTime);
}

void PlayScene::ChangeIcon() {
	switch (OBJECT->GetPlayer()->GetItemState()) {
		case ITEM_PISTOL: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
			NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOff"))));
			NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOff"))));
			break;
		}
		case ITEM_MACHINEGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOn"))));
			NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOff"))));
			break;
		}
		case ITEM_LASERGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOff"))));
			NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOn"))));
			break;
		}
	}
}

void PlayScene::OnExit()
{
	//Exit	
}

void PlayScene::OnDraw()
{	

	// 배경 그려주는 부분 (보이는 화면 좌우로 하나씩 더)
	DrawBG();

	// 임시 미니맵 배경
	//pMinimapCamera->Draw(m_pMinimap, Vector(0,0));
	pMinimapCamera->Draw(m_pRadar, Vector(-24, 24));

	// 미니맵 시야 각도 표시
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT, 
		MINI_WIDTH * 0.5 - MINI_WIDTH * 0.5 * MATH->Sin(CAMERA_ANGLE * 0.5), MINI_HEIGHT - MINI_WIDTH * 0.5 * MATH->Cos(CAMERA_ANGLE * 0.5), ColorF::Blue, 2);
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT,
		MINI_WIDTH * 0.5 + MINI_WIDTH * 0.5 * MATH->Sin(CAMERA_ANGLE * 0.5), MINI_HEIGHT - MINI_WIDTH * 0.5 * MATH->Cos(CAMERA_ANGLE * 0.5), ColorF::Blue, 2);
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT, MINI_WIDTH * 0.5, MINI_HEIGHT - MINI_WIDTH * 0.5, ColorF::Blue, 1);

	// 미니맵 크리쳐 생성되는 범위 표시	
	//pMinimapCamera->DrawCircle(Vector(MINI_WIDTH * 0.5, MINI_HEIGHT), Vector(MINI_WIDTH, MINI_WIDTH), ColorF::Yellow);

	// 미니맵에 플레이어 위치 표시
	pMinimapCamera->DrawFilledCircle(Vector(MINI_WIDTH * 0.5 , MINI_HEIGHT), Vector(8, 8), ColorF::Yellow);

	// 미니맵에 크리쳐 위치 표시
	list<Object*> pList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, pList)
	{
		Vector pos = (*it)->Position();
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::Red);
		pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::Red, 2);
	}

	//탄환 선 긋기
	list<Object*> pBulletList = OBJECT->GetBulletList();
	FOR_LIST(Object*, pBulletList)
	{
		Vector pos = (*it)->Position();
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::DeepPink);
		pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::DeepPink, 2);
	}
	
	OBJECT->Draw(pMainCamera);
	
	/*pUICamera->Draw(OBJECT->GetPlayer()->Animation()->Current()->GetSprite(), Vector(VIEW_WIDTH * 0.5, VIEW_HEIGHT * 1.0f));*/

	// Aim 그려주는 부분
	pUICamera->Draw(m_pAim, Vector(VIEW_WIDTH * 0.5, VIEW_HEIGHT * 0.5f));

	//Bunker 체력
	pUICamera->DrawRect(Vector(20, 20), Vector(260, 50), ColorF::Blue, 1);

	//Icon
	pUICamera->Draw(m_ico_pistol, Vector(40, 110));
	pUICamera->Draw(m_ico_machine, Vector(110, 110));
	pUICamera->DrawRect(Vector(160, 90), Vector(50, 50), ColorF::Red, 1);
	pUICamera->Draw(m_ico_laser, Vector(250, 110));


	pUICamera->DrawRect(Vector(20, VIEW_HEIGHT - 190), Vector(320, 70), ColorF::Blue, 1);
	pUICamera->DrawRect(Vector(20, VIEW_HEIGHT - 100), Vector(70, 70), ColorF::Red, 1);
	pUICamera->DrawRect(Vector(110, VIEW_HEIGHT - 100), Vector(70, 70), ColorF::Red, 1);
	pUICamera->DrawRect(Vector(200, VIEW_HEIGHT - 100), Vector(70, 70), ColorF::Red,1);
	pUICamera->DrawRect(Vector(290, VIEW_HEIGHT - 100), Vector(70, 70), ColorF::Red,1);

	pUICamera->DrawT(TEXT("Stage 1"), VIEW_WIDTH / 2-50, 40, ColorF::White, 30, ALIGN_CENTER);
	pUICamera->DrawT(TEXT("점수 : "), VIEW_WIDTH - 300, 30, ColorF::White, 30, ALIGN_RIGHT);
	pUICamera->DrawT(TEXT("골드 : "), VIEW_WIDTH - 300, 70, ColorF::White, 30, ALIGN_RIGHT);
}

void PlayScene::SetCreature(float deltaTime)
{
	int creatureLimit = m_gameTime / 3;
	if (m_createdCretureCount < creatureLimit)
	{
		int x = rand() % MINI_WIDTH * 0.5;
		if (rand() % 2 == 0) x *= -1;

		int y = sqrt(pow(MINI_WIDTH * 0.5f, 2) - pow(x, 2));
		if (rand() % 2 == 0) y *= -1;

		if (y >= 0)
		{
			y = MINI_HEIGHT - y;
		}
		else
		{
			y = MINI_HEIGHT + y;
		}

		x = x + MINI_WIDTH * 0.5;
		OBJECT->CreateCreature(OBJ_ENT, Vector(x, y));
		m_createdCretureCount++;
	}

}

void PlayScene::DrawBG()
{
	Vector bgPos = OBJECT->GetAimPos();
	pMainCamera->Draw(m_pBg, bgPos);

	if(bgPos.x > 0) pMainCamera->Draw(m_pBg, bgPos - Vector(1920 * 2 * 1.8, 0));
	else pMainCamera->Draw(m_pBg, bgPos + Vector(1920 * 2 * 1.8, 0));
}