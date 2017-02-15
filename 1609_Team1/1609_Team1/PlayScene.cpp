#include "PlayScene.h"



PlayScene::PlayScene() : m_attackedColor(ColorF::Red)
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

	//인터페이스 UI 이미지 가져오기
	RENDER->LoadImageFile(TEXT("StageFont_UI"), TEXT("Image/UI/InterfaceUI/stage.png"));
	RENDER->LoadImageFile(TEXT("Bunker_UI"), TEXT("Image/UI/InterfaceUI/Bunker_UI.png"));
	RENDER->LoadImageFile(TEXT("ItemBar_UI"), TEXT("Image/UI/InterfaceUI/ItemBarUI.png"));
	RENDER->LoadImageFile(TEXT("ScoreUI"), TEXT("Image/UI/InterfaceUI/Score.png"));
	RENDER->LoadImageFile(TEXT("MoneyUI"), TEXT("Image/UI/InterfaceUI/money.png"));

	//Bullet 임시로 저장
	RENDER->LoadImageFiles(TEXT("BulletIdle"), TEXT("Image/Bullet/bullet"), TEXT("png"), 1);

	//무기 ICON 가져오기
	RENDER->LoadImageFile(TEXT("PistolOn"),		TEXT("Image/Item/Icon/ico_pistol_on.png"));
	RENDER->LoadImageFile(TEXT("PistolOff"),	TEXT("Image/Item/Icon/ico_pistol_off.png"));
	RENDER->LoadImageFile(TEXT("LaserOn"),		TEXT("Image/Item/Icon/ico_laser_on.png"));
	RENDER->LoadImageFile(TEXT("LaserOff"),		TEXT("Image/Item/Icon/ico_laser_off.png"));
	RENDER->LoadImageFile(TEXT("MachineOn"),	TEXT("Image/Item/Icon/ico_machine_on.png"));
	RENDER->LoadImageFile(TEXT("MachineOff"),	TEXT("Image/Item/Icon/ico_machine_off.png"));

	// 벙커 체력 막대 생성
	m_bunkerLife = new UIProgressBar(Vector(140, 35), Vector(240, 30), ColorF::Green, ColorF::LightYellow);
	m_bunkerLife->SetMinMaxColor(ColorF::Red, ColorF::Green);

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

	// UI 이미지 생성
	NEW_OBJECT(m_stageUI, Sprite(RENDER->GetImage(TEXT("StageFont_UI"))));
	NEW_OBJECT(m_ScoreUI, Sprite(RENDER->GetImage(TEXT("ScoreUI")),0.8f));
	NEW_OBJECT(m_MoneyUI, Sprite(RENDER->GetImage(TEXT("MoneyUI")), 0.8f));
	NEW_OBJECT(m_BunkerUI, Sprite(RENDER->GetImage(TEXT("Bunker_UI"))));
	NEW_OBJECT(m_ItemBarUI, Sprite(RENDER->GetImage(TEXT("ItemBar_UI"))));

	//ico pistol
	NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
	NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOff"))));
	NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOff"))));	

	// 플레이어 생성
	OBJECT->CreatePlayer(Vector(MINI_WIDTH * 0.5F, MINI_HEIGHT), Vector(10, 10), Vector(0.5f, 1.0f));

	// 벙커 생성
	OBJECT->CreateBunker();
	Object* pObj = OBJECT->GetBunker();

	// 크리쳐 공격 연출을 위한 도구(색 저장용) 투명도 초기화
	m_attackedColor.a = 0;

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

	// 벙커 체력 UIProgressBar 업데이트(이것은 벙커 객체 소유물이 아닌 UI이므로 플레이씬에서 가지고 업데이트 하는 것이 맞아보임)
	m_bunkerLife->SetTargetValue(OBJECT->GetBunker()->GetCurrentLife() / OBJECT->GetBunker()->GetMaxLife());
	m_bunkerLife->Update(deltaTime);

	if(m_attackedColor.a != 0) m_attackedColor.a = MATH->Clamp(m_attackedColor.a - deltaTime * 10, 0.0f, 20.0f);
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

	//플레이 UI출력
	//1.Stage UI 출력
	pUICamera->Draw(m_stageUI, Vector(600, 100));
	pUICamera->DrawRect(Vector(565, 125), Vector(70, 70), ColorF::Red, 3);
	pUICamera->DrawT(TEXT("1"), 590, 140, ColorF::Red, 30, ALIGN_RIGHT);
	//pUICamera->DrawT(TEXT("Stage 1"), VIEW_WIDTH / 2 - 50, 40, ColorF::White, 30, ALIGN_CENTER);

	//2.벙커UI / 스킬 UI
	pUICamera->Draw(m_BunkerUI, Vector(150, 80));
	pUICamera->Draw(m_ItemBarUI, Vector(200, 790));
	
	//3.점수 출력
	//pUICamera->DrawT(TEXT("점수 : "), VIEW_WIDTH - 300, 30, ColorF::White, 30, ALIGN_RIGHT);
	//pUICamera->DrawT(TEXT("골드 : "), VIEW_WIDTH - 300, 70, ColorF::White, 30, ALIGN_RIGHT);
	pUICamera->Draw(m_ScoreUI, Vector(VIEW_WIDTH - 300, 45));
	pUICamera->DrawRect(Vector(VIEW_WIDTH - 220, 25), Vector(200, 35), ColorF::Red, 5);
	pUICamera->Draw(m_MoneyUI, Vector(VIEW_WIDTH - 300, 100));
	pUICamera->DrawRect(Vector(VIEW_WIDTH - 220, 80), Vector(200, 35), ColorF::Red, 5);

	// 크리쳐에게 공격 받았음을 나타내기 위한 부분
	if (m_attackedColor.a != 0) pUICamera->DrawFilledRect(Vector(0,0), Vector(VIEW_WIDTH, VIEW_HEIGHT), m_attackedColor);

	//Bunker 체력
	m_bunkerLife->Render();

	//Icon
	pUICamera->Draw(m_ico_pistol, Vector(50, 110));
	pUICamera->Draw(m_ico_machine, Vector(112, 110));
	pUICamera->DrawRect(Vector(150, 85), Vector(50, 50), ColorF::Red, 1);
	pUICamera->Draw(m_ico_laser, Vector(242, 110));


	pUICamera->DrawRect(Vector(40, VIEW_HEIGHT - 195), Vector(320, 70), ColorF::Blue, 1);
	pUICamera->DrawRect(Vector(30, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red, 1);
	pUICamera->DrawRect(Vector(120, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red, 1);
	pUICamera->DrawRect(Vector(210, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red,1);
	pUICamera->DrawRect(Vector(300, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red,1);


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