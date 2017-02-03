#pragma once
#include "ObjectManager.h"
class Player :
	public Object
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);
};

