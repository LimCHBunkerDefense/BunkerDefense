#include "PlayScene.h"



PlayScene::PlayScene()
{
	RENDER->LoadImageFile(TEXT("TownBg"), TEXT("Image/TownBg.jpg"));
	RENDER->CreateCamera(CAM_MAIN, 3000, 1000, VIEW_WIDTH, VIEW_HEIGHT);


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

	m_example.Update(deltaTime);
}

void PlayScene::OnExit()
{
	//Exit	
}

void PlayScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMainCamera->Draw(m_pBg, Vector(0, 0));
	m_example.Render();
}