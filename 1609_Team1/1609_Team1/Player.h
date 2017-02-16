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
	float m_greCoolTime;
	Object* m_pItem;						// 아이템
	map<int, Object*> m_itemBag;			// 아이템 가방

	PLAYER_STATE m_state;			    	// 플레이어 상태
	ITEM_TAG item_state;			    	// 아이템 가진 상태
	GRENADE_STATE gre_state;				// 수류탄 가진 상태
										   
	Vector m_prevMousePos;				    // 이전 마우스 좌표값
	float HitPoint;
	//float m_sight;						// 시야 길이

	int m_money;
	int m_score;


public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

//	void ThrowState(float deltaTime);
	void AttackState(float deltaTime);
	void ShopState();

	// 아이템을 가방에 추가하는 함수
	void AddItem(Object* pItem); 

	// 번호 입력시 아이템을 장착하는 함수
	void SetItem();

	// 현재 장착무기 호출
	Object* GetCurrentItem() { return m_pItem; }

	ITEM_TAG GetItemState() { return item_state; }

	// 플레이어의 점수 및 돈 호출/추가 함수
	int GetScore() { return m_score; }
	void AddScore(int addScore) { m_score += addScore; }
	int GetMoney() { return m_money; }
	void AddMoney(int addMoney) { m_money += addMoney; }
	map<int, Object*> GetItemBag() { return m_itemBag; }
};

