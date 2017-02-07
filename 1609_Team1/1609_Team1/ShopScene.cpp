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
	
	m_bBuyButton = Box(Vector(1000, 500), Vector(100, 50));
	m_bWeapon = Box(Vector(450, 450), Vector(200, 50));
	m_bBullet = Box(Vector(450, 500), Vector(200, 50));
	m_bItem = Box(Vector(450, 550), Vector(200, 50));
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
		RENDER->DrawRect(m_bBuyButton.LeftTop() + m_bBuyButton.size * 0.5f, m_bBuyButton.size, ColorF::Yellow, 3.0f);
		
		RENDER->DrawRect(m_bWeapon.LeftTop() + m_bWeapon.size * 0.5f, m_bWeapon.size, ColorF::Yellow, 3.0f);
		RENDER->DrawRect(m_bBullet.LeftTop() + m_bBullet.size * 0.5f, m_bBullet.size, ColorF::Yellow, 3.0f);
		RENDER->DrawRect(m_bItem.LeftTop() + m_bItem.size * 0.5f, m_bItem.size, ColorF::Yellow, 3.0f);
		
		
		// RENDER->DrawRect(m_bMachineGun.LeftTop() + m_bMachineGun.size * 0.5f, m_bMachineGun.size, ColorF::Yellow, 3.0f);
		// RENDER->DrawRect(m_bFireThrower.LeftTop() + m_bFireThrower.size * 0.5f, m_bFireThrower.size, ColorF::Yellow, 3.0f);
		// RENDER->DrawRect(m_bPistolBullet.LeftTop() + m_bPistolBullet.size * 0.5f, m_bPistolBullet.size, ColorF::Yellow, 3.0f);
		// RENDER->DrawRect(m_bMachineGunBullet.LeftTop() + m_bMachineGunBullet.size * 0.5f, m_bMachineGunBullet.size, ColorF::Yellow, 3.0f);
		// RENDER->DrawRect(m_bFireThrowerBullet.LeftTop() + m_bFireThrowerBullet.size * 0.5f, m_bFireThrowerBullet.size, ColorF::Yellow, 3.0f);
		// RENDER->DrawRect(m_bGrenade.LeftTop() + m_bGrenade.size * 0.5f, m_bGrenade.size, ColorF::Yellow, 3.0f);
		// RENDER->DrawRect(m_bAirBomb.LeftTop() + m_bAirBomb.size * 0.5f, m_bAirBomb.size, ColorF::Yellow, 3.0f);
		// RENDER->DrawRect(m_bRavaRegion.LeftTop() + m_bRavaRegion.size * 0.5f, m_bRavaRegion.size, ColorF::Yellow, 3.0f);
		// RENDER->DrawRect(m_bBunckerRepair.LeftTop() + m_bBunckerRepair.size * 0.5f, m_bBunckerRepair.size, ColorF::Yellow, 3.0f);
	}
}

void ShopScene::ItemListWnd()
{
	RENDER->DrawRect(Vector(400, 450),Vector(400, 650),ColorF::Red);
	RENDER->DrawT(TEXT("ITEM LIST"), 350, 400, ColorF::Red, 25);
}
void ShopScene::ItemStatWnd()
{
	RENDER->DrawRect(Vector(800, 450), Vector(400, 650), ColorF::Yellow);
	RENDER->DrawT(TEXT("ITEM INFO"), 750, 400, ColorF::Red, 25);
}