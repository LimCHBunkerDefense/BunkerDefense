#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "Common.h"

class ShopScene :
	public IScene
{
public:
	ShopScene();
	~ShopScene();

	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();
};

