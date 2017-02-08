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
	BUTTON_TAG m_currentButton;

	// 상점의 중분류 버튼이 클릭되었나를 확인하는 bool 변수
	bool IsWeaponClicked;
	bool IsBulletClicked;
	bool IsUsingItemClicked;

public:
	ShopScene();
	~ShopScene();
	
	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void ItemListWnd();											// 아이템 리스트 창
	void ItemStatWnd();											// 아이템 정보 창

	Item* GetSelectedItem() { return m_selectedItem; }
	void SetCurrentButton(BUTTON_TAG buttonTag) { m_currentButton = buttonTag; }

	void SetIsWeaponClicked(bool ON) { IsWeaponClicked = ON; }
	void SetIsBulletClicked(bool ON) { IsBulletClicked = ON; }
	void SetIsUsingItemClicked(bool ON) { IsUsingItemClicked = ON; }
};

