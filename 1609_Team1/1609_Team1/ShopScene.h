#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Common.h"
#include <list>
#include "Item.h"

class ShopScene :
	public IScene
{
	Sprite* m_pBg;
	Box m_buyButton;

	Box m_weapon1;
	Box m_weapon2;
	Box m_weapon3;

	Item* m_selectedItem;
	list<Item*> m_itemList;


public:
	ShopScene();
	~ShopScene();
	
	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void ItemListWnd(); // 아이템 리스트 창
	void ItemStatWnd(); // 아이템 정보 창

	Box GetButton() { return m_buyButton; }
	Item* GetSelectedItem() { return m_selectedItem; }
};

