#pragma once
#include "ObjectManager.h"
class Player :
	public Object
{
public:
	Player();
	~Player();

	Player(int id) : Object(id)
	{
		
	}

	void Update(float deltaTime);
	void Draw(Camera* pCamera);
};

