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

public:
	ShopScene();
	~ShopScene();

	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void ItemListWnd(); // 아이템 리스트 창
	void ItemStatWnd(); // 아이템 정보 창
};

