#include "PlayScene.h"



PlayScene::PlayScene()
{
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

	// 테스트용 크리쳐 생성
	OBJECT->CreateCreature(OBJ_ENT, Vector(500, 500), Vector(100, 100));

	// 플레이어 생성
	OBJECT->CreatePlayer(Vector(VIEW_WIDTH * 0.5F, VIEW_HEIGHT), Vector(10, 10), Vector(0.5f, 1.0f));

	// 카메라 세팅
	RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->GetCamera(CAM_MINIMAP)->SetScreenRect(VIEW_WIDTH - MINI_WIDTH/2, VIEW_HEIGHT, MINI_WIDTH, MINI_HEIGHT);
}

void PlayScene::OnUpdate(float deltaTime)
{
	OBJECT->Update(deltaTime);
	m_example.Update(deltaTime);

	if (INPUT->IsKeyDown(VK_F3))
	{
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

void PlayScene::Test()
{

}