#pragma once
#include "ObjectManager.h"
#include "Item.h"
class Player :
	public Object
{
	Item* m_pItem;
		
	PLAYER_STATE m_state;
	
public:
	Player();
	Player(OBJ_TAG tag);
	~Player();

	

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void AttackState(float deltaTime);
	void ShopState();
};

