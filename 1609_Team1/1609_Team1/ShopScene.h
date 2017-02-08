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

	// ������ �ߺз� ��ư�� Ŭ���Ǿ����� Ȯ���ϴ� bool ����
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

	void ItemListWnd();											// ������ ����Ʈ â
	void ItemStatWnd();											// ������ ���� â

	Item* GetSelectedItem() { return m_selectedItem; }
	void SetCurrentButton(BUTTON_TAG buttonTag) { m_currentButton = buttonTag; }

	void SetIsWeaponClicked(bool ON) { IsWeaponClicked = ON; }
	void SetIsBulletClicked(bool ON) { IsBulletClicked = ON; }
	void SetIsUsingItemClicked(bool ON) { IsUsingItemClicked = ON; }
};

