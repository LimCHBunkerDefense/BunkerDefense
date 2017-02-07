#include "PlayScene.h"



PlayScene::PlayScene()
{
	// 크리쳐 생성되는 높이h값 생성. 추후 마우스에 따라 실시간 변화
	m_heightOfCreature = 300;


	// 배경 이미지 맵으로 저장
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); //경로 루트 변경 배경이미지 폴더 생성.

	// 크리쳐 데이터 생성
	CREATURE->Init();
	
	// 크리처 이미지 맵으로 저장
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 9);

	// 카메라 생성
	RENDER->CreateCamera(CAM_MAIN, 1920, 1200, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->CreateCamera(CAM_MINIMAP, MINI_WIDTH, MINI_HEIGHT * 2, MINI_WIDTH, MINI_HEIGHT);

}


PlayScene::~PlayScene()
{
}


void PlayScene::OnEnter()
{
	// 배경 이미지 스프라이트로 생성
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("ForestBG")), 1.0f, 0, 0));

	// 플레이어 생성
	OBJECT->CreatePlayer(Vector(VIEW_WIDTH * 0.5F, VIEW_HEIGHT), Vector(10, 10), Vector(0.5f, 1.0f));

	// 카메라 세팅
	RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->GetCamera(CAM_MINIMAP)->SetScreenRect(VIEW_WIDTH - MINI_WIDTH/2, VIEW_HEIGHT, MINI_WIDTH, MINI_HEIGHT);
}

void PlayScene::OnUpdate(float deltaTime)
{
	// 크리쳐 생성을 위한 게임 시간 업데이트
	m_gameTime += deltaTime;

	// 게임 시간에 따른 크리쳐 생성
	SetCreature(deltaTime);
	
	// 오브젝트 전체 업데이트
	OBJECT->Update(deltaTime);

	// 씬 채인지 추가 (170207 김윤중)
	if (INPUT->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene(SCENE_SHOP);
	}

}

void PlayScene::OnExit()
{
	//Exit	
}

void PlayScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	Camera* pMinimapCamera = RENDER->GetCamera(CAM_MINIMAP);

	pMainCamera->Draw(m_pBg, Vector(0, 0));
	pMainCamera->DrawFilledRect(OBJECT->GetPlayer()->Position() - Vector(50, 50), Vector(100, 100), ColorF::Aqua);
	OBJECT->Draw(pMainCamera);
}

void PlayScene::SetCreature(float deltaTime)
{
	
	int x = rand() % 1200;
	OBJECT->CreateCreature(OBJ_ENT, Vector(x, m_heightOfCreature));
}