#include "PlayScene.h"



PlayScene::PlayScene()
{
	// 크리쳐 생성되는 높이h값 생성. 추후 마우스에 따라 실시간 변화
	m_heightOfCreature = 600;


	// 배경 이미지 맵으로 저장
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); 
	RENDER->LoadImageFile(TEXT("DroughtBG"), TEXT("Image/BackGround/DroughtBG.jpg"));

	// 크리쳐 데이터 생성
	CREATURE->Init();
	
	// 크리처 이미지 맵으로 저장
	RENDER->LoadImageFiles(TEXT("EntIdle"), TEXT("Image/Creature/Ent/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 9);
	RENDER->LoadImageFiles(TEXT("EntAttack"), TEXT("Image/Creature/Ent/Attack/Attack"), TEXT("png"), 6);

	// 카메라 생성
	RENDER->CreateCamera(CAM_MAIN, 1920, 1080, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->CreateCamera(CAM_MINIMAP, MINI_WIDTH, MINI_HEIGHT* 2, MINI_WIDTH, MINI_HEIGHT * 2);

}


PlayScene::~PlayScene()
{
}


void PlayScene::OnEnter()
{
	// 배경 이미지 스프라이트로 생성
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("DroughtBG")), 1.0f, 0, 0));

	// 플레이어 생성
	OBJECT->CreatePlayer(Vector(MINI_WIDTH * 0.5F, MINI_HEIGHT), Vector(10, 10), Vector(0.5f, 1.0f));

	// 카메라 세팅
	RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->GetCamera(CAM_MINIMAP)->SetScreenRect(VIEW_WIDTH - MINI_WIDTH, VIEW_HEIGHT - MINI_HEIGHT * 2, MINI_WIDTH, MINI_HEIGHT * 2);

	m_createdCretureCount = 0;

	// 테스트용 크리쳐 생성
	//OBJECT->CreateCreature(OBJ_ENT, Vector(120, 60));

	// 마우스 커서 없애기
	ShowCursor(false);

}

void PlayScene::OnUpdate(float deltaTime)
{
	// 크리쳐 생성을 위한 게임 시간 업데이트
	m_gameTime += deltaTime;

	// 게임 시간에 따른 크리쳐 생성
	SetCreature(deltaTime);
	
	// 오브젝트 전체 업데이트
	OBJECT->Update(deltaTime);
	OBJECT->SetPosByDeltaAngle();
}

void PlayScene::OnExit()
{
	//Exit	
}

void PlayScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	Camera* pMinimapCamera = RENDER->GetCamera(CAM_MINIMAP);

	// 배경 그려주는 부분
	DrawBG();

	// 임시 미니맵 배경
	pMinimapCamera->DrawFilledRect(Vector(0, 0), Vector(MINI_WIDTH, MINI_HEIGHT), ColorF::Green);

	// 미니맵 시야 각도 표시
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT, 
		MINI_WIDTH * 0.5 - MINI_WIDTH * 0.5 * MATH->Sin(CAMERA_ANGLE * 0.5), MINI_HEIGHT - MINI_WIDTH * 0.5 * MATH->Cos(CAMERA_ANGLE * 0.5), ColorF::Blue, 2);
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT,
		MINI_WIDTH * 0.5 + MINI_WIDTH * 0.5 * MATH->Sin(CAMERA_ANGLE * 0.5), MINI_HEIGHT - MINI_WIDTH * 0.5 * MATH->Cos(CAMERA_ANGLE * 0.5), ColorF::Blue, 2);
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT, MINI_WIDTH * 0.5, MINI_HEIGHT - MINI_WIDTH * 0.5, ColorF::Blue, 1);

	// 미니맵 크리쳐 생성되는 범위 표시	
	pMinimapCamera->DrawCircle(Vector(MINI_WIDTH * 0.5, MINI_HEIGHT), Vector(MINI_WIDTH, MINI_WIDTH), ColorF::Yellow);

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



	OBJECT->Draw(pMainCamera);
}

void PlayScene::DrawBG()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMainCamera->Draw(m_pBg, m_posBg);

	if (m_posBg.x < 0) pMainCamera->Draw(m_pBg, m_posBg + m_pBg->GetWidth());
	if (m_posBg.x > 0) pMainCamera->Draw(m_pBg, m_posBg - m_pBg->GetWidth());

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