#include "PlayScene.h"



PlayScene::PlayScene()
{
	RENDER->LoadImageFile(TEXT("TownBg"), TEXT("Image/TownBg.jpg"));
	RENDER->CreateCamera(CAM_MAIN, 3000, 1000, VIEW_WIDTH, VIEW_HEIGHT);
	OBJECT->CreatePlayer(Vector(100, 600), Vector(100, 100), Vector(0.5f, 1.0f));
}


PlayScene::~PlayScene()
{
}


void PlayScene::OnEnter()
{
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("TownBg")), 1.0f, 0, 0));
	RENDER->GetCamera(CAM_MAIN)->SetScreenRect(100, 100, 600, 400);
}

void PlayScene::OnUpdate(float deltaTime)
{
	RENDER->GetCamera(CAM_MAIN)->SetCenterPos(OBJECT->GetPlayer()->Position());
}

void PlayScene::OnExit()
{
	//Exit	
}

void PlayScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMainCamera->Draw(m_pBg, Vector(0, 0));
	OBJECT->Draw(pMainCamera);
}