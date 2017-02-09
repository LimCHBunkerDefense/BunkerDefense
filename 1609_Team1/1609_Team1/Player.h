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
	Item* m_pItem;						// 아이템
	map<int, Item*> m_itemBag;			// 아이템 가방

	PLAYER_STATE m_state;				// 플레이어 상태
	GUN_STATE m_gunState;				// 플레이어가 들고 있는 총의 상태

	Vector m_vAngle;					// 플레이어 보는 각도
										   
	Vector m_prevMousePos;				// 이전 마우스 좌표값
	float m_sight;						// 시야 길이



public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void AttackState(float deltaTime);
	void ShopState();

	// 아이템을 가방에 추가하는 함수
	void AddItem(Item* pItem) { m_itemBag[pItem->GetID()] = new Item(pItem->GetID()); }

	// 번호 입력시 아이템을 장착하는 함수
	void SetItem();
};

