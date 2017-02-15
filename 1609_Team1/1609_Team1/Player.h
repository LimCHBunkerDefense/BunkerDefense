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
	Object* m_pItem;						// 아이템
	map<int, Object*> m_itemBag;			// 아이템 가방

	PLAYER_STATE m_state;			    	// 플레이어 상태
	ITEM_TAG item_state;			    	// 아이템 가진 상태
										   
	Vector m_prevMousePos;				    // 이전 마우스 좌표값

	float HitPoint;
	//float m_sight;						// 시야 길이

public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void AttackState(float deltaTime);
	void ShopState();

	// 아이템을 가방에 추가하는 함수
	void AddItem(Object* pItem); 

	// 번호 입력시 아이템을 장착하는 함수
	void SetItem();

	ITEM_TAG GetItemState() { return item_state; }
	map<int, Object*> GetItemBag() { return m_itemBag; }
};

