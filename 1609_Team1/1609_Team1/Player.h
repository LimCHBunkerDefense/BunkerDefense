#pragma once
#include "ObjectManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Item.h"
#include "InputManager.h"
#include "Math.h"


class Player :
	public Object
{
	Item* m_pItem;
	list<Item*> m_itemList;

	PLAYER_STATE m_state;
	
public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void AttackState(float deltaTime);
	void ShopState();

	void AddItem(Item* pItem) { m_itemList.push_back(pItem); }
};

