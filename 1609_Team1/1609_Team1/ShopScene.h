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

	void ItemListWnd(); // ������ ����Ʈ â
	void ItemStatWnd(); // ������ ���� â
};

