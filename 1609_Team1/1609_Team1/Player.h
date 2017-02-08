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

	Vector m_vAngle;//플레이어 보는 각도

	float m_angle;//회전 각도

	Vector PrevMousePos;//이전 마우스 좌표값
	float Sight;//시야 길이



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

