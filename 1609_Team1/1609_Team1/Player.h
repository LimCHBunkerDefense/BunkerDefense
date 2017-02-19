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
	PLAYER_ANISTATE ani_state;				//애니메이션 출력용 변수
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

	// 총 이미지에 따라 그려주는 위치 새로 설정
	Vector DrawPos();

//	void ThrowState(float deltaTime);
	void AttackState(float deltaTime);
	void ShopState();

	// 아이템을 가방에 추가하는 함수
	void AddItem(Object* pItem); 

	// 번호 입력시 아이템을 장착하는 함수
	void SetItem();

	// 총쏘는 애니메이션 끝나면 현재 아이템의 Idle애니메이션으로 돌려주는 함수
	void SetIdleAnimation();

	// 총 쏠 때 애니메이션 변경해주는 함수
	void SetShotAnimation();

	// 현재 장착무기 호출
	Object* GetCurrentItem() { return m_pItem; }

	ITEM_TAG GetItemState() { return item_state; }
	GRENADE_STATE GetGreState() { return gre_state; }

	// 플레이어의 점수 및 돈 호출/추가 함수
	int GetScore() { return m_score; }
	void AddScore(int addScore) { m_score += addScore; }
	int GetMoney() { return m_money; }
	void AddMoney(int addMoney) { m_money += addMoney; }
	map<int, Object*> GetItemBag() { return m_itemBag; }
};

