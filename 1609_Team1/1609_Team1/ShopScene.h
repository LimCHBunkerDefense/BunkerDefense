#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Common.h"
#include "Item.h"

class ShopScene :
	public IScene
{
	Sprite* m_pBg;
	Box m_bBuyButton;

	Box m_bWeapon;
	Box m_bBullet;
	Box m_bItem;

	Box m_bMachineGun;				// 머신건
	Box m_bFireThrower;				// 화염방사기

	Box m_bPistolBullet;			// 권총 탄약
	Box m_bMachineGunBullet;		// 머신건 탄약
	Box m_bFireThrowerBullet;		// 화염방사기 탄약

	Box m_bGrenade;					// 수류탄
	Box m_bAirBomb;					// 공중 폭격
	Box m_bRavaRegion;				// 화염 지대
	Box m_bBunckerRepair;			// 벙커 수리

	Item* m_selectedItem;
public:
	ShopScene();
	~ShopScene();
	
	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void ItemListWnd(); // 아이템 리스트 창
	void ItemStatWnd(); // 아이템 정보 창

	Box GetButton() { return m_bBuyButton; }
	Item* GetSelectedItem() { return m_selectedItem; }
};

