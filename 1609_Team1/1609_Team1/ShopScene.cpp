#include "ShopScene.h"

ShopScene::ShopScene()
{
	RENDER->LoadImageFile(TEXT("shopBG"), TEXT("Image/BackGround/shopBG.png"));

}


ShopScene::~ShopScene()
{
}

void ShopScene::OnEnter()
{
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("shopBG")), 1.0f, 0, 0));
	
}

void ShopScene::OnUpdate(float deltaTime)
{
	ItemListWnd();
	ItemStatWnd();
}

void ShopScene::OnExit()
{
	
}

void ShopScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMainCamera->Draw(m_pBg, Vector(0, 0));
}

void ShopScene::ItemListWnd()
{
	RENDER->DrawRect(Vector(200,400),Vector(250,550),ColorF::Red);
}
void ShopScene::ItemStatWnd()
{
	RENDER->DrawRect(Vector(1000, 400), Vector(250, 550), ColorF::Yellow);
}