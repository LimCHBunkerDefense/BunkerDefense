#pragma once
#include "Singleton.h"
#include "Common.h"
#include "Math.h"
#include "RenderManager.h"
#include <map>

#define ITEM ItemDB::Instance()

struct ItemData
{
	ITEMTYPE_TAG iTag;			// 중분류 아이템 태그 
	ITEM_TAG tag;				// 소분류 아이템 태그
	int itemID;					// 아이템에 대한 ID값
	int money;					// 아이템 구매에 필요한 돈
	float attack;				// 능력치 - 공격력	
	float range;				// 능력치 - 사정거리
	float repair;					// 수리량
	float bulletSpeed;			// 총알 속도
	float bunkerLife;			// 벙커 체력
	int maxBulletCount;			// 총에 장착하는 총알의 갯수
	int reloadBulletCount;		// 장전할 수 있는 총알의 갯수
	int maxCount;				// 아이템을 구매할 수 있는 최대 갯수
	wstring name;				// 아이템 이름
	wstring info;				// 아이템 정보
	wstring ragestr;			// 사정거리 표시 이름
		
	ItemData(ITEMTYPE_TAG iTag, ITEM_TAG tag, int itemID, float attack, float range, float repair, float bulletSpeed,
		float bunkerLife, int maxBulletCount, int reloadBulletCount, int maxCount, int money, 
		wstring name, wstring info, wstring ragestr = TEXT(" "))
	{
		this->iTag = iTag;
		this->tag = tag;
		this->itemID = itemID;
		this->attack = attack;
		this->range = range;
		this->repair = repair;
		this->bulletSpeed = bulletSpeed;
		this->bunkerLife = bunkerLife;
		this->maxBulletCount = maxBulletCount;
		this->reloadBulletCount = reloadBulletCount;
		this->maxCount = maxCount;
		this->money = money;
		this->name = name;
		this->info = info;
		this->ragestr = ragestr;
	}

public:
};


class ItemDB : public Singleton<ItemDB>
{
	map<int, ItemData*> m_pItems;
public:
	ItemDB();
	~ItemDB();

	void Init();
	void Add(ItemData* pData);
	int GetItem(int itemID) { return itemID; }
	ItemData* GetData(int itemID);
};

