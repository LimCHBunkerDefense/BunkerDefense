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
	
	m_buyButton = Box(Vector(1000, 500), Vector(100, 50));
	m_weapon1 = Box(Vector(600, 300), Vector(100, 50));
	m_weapon2 = Box(Vector(600, 400), Vector(100, 50));
	m_weapon3 = Box(Vector(600, 500), Vector(100, 50));
}

void ShopScene::OnUpdate(float deltaTime)
{
	OBJECT->Update(deltaTime);

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
	RENDER->DrawRect(Vector(1100, 800), Vector(150, 50), ColorF::Blue);
	RENDER->DrawT(TEXT("³ª°¡±â F3"), 1050, 785, ColorF::Red, 25);

	if (SCENE->GetColliderOnOff())
	{
		RENDER->DrawRect(m_buyButton.LeftTop() + m_buyButton.size * 0.5f, m_buyButton.size, ColorF::Yellow, 3.0f);
		RENDER->DrawRect(m_weapon1.LeftTop() + m_weapon1.size * 0.5f, m_weapon1.size, ColorF::Yellow, 3.0f);
		RENDER->DrawRect(m_weapon2.LeftTop() + m_weapon2.size * 0.5f, m_weapon2.size, ColorF::Yellow, 3.0f);
		RENDER->DrawRect(m_weapon3.LeftTop() + m_weapon3.size * 0.5f, m_weapon3.size, ColorF::Yellow, 3.0f);
	}
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