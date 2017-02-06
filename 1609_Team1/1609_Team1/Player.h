#pragma once
#include "ObjectManager.h"
#include "Item.h"
class Player :
	public Object
{
	Item* m_pItem;

	
public:
	Player();
	~Player();

	Player(int id) : Object(id)
	{
		
	}

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void AttackState(float deltaTime);
	void ShopState();
};

