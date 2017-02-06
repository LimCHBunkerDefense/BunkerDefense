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
	RENDER->DrawRect(Vector(620, 50), Vector(150, 50), ColorF::Blue);
	RENDER->DrawT(TEXT("SHOP"), 590, 35, ColorF::Red, 25);

}

void ShopScene::ItemListWnd()
{
	RENDER->DrawRect(Vector(400,450),Vector(400,650),ColorF::Red);
	RENDER->DrawT(TEXT("ITEM LIST"), 350, 400, ColorF::Red, 25);
}
void ShopScene::ItemStatWnd()
{
	RENDER->DrawRect(Vector(800, 450), Vector(400, 650), ColorF::Yellow);
	RENDER->DrawT(TEXT("ITEM INFO"), 750, 400, ColorF::Red, 25);
}