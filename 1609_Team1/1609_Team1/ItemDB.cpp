#include "ItemDB.h"



ItemDB::ItemDB()
{
}


ItemDB::~ItemDB()
{
}

void ItemDB::Init()
{
	// 기본 무기
	Add(new ItemData(ITEM_WEAPON, 1001, 10, 0, 0, 50,   0, 0,   TEXT("권총")));
	
	// 상점 구매 무기
	Add(new ItemData(ITEM_WEAPON, 1002, 30, 0, 0, 1000, 0, 2000, TEXT("기관총")));
	Add(new ItemData(ITEM_WEAPON, 1003, 50, 0, 0, 700,  0, 1500, TEXT("화염 방사기")));
	Add(new ItemData(ITEM_WEAPON, 1004, 50, 0, 0, 1500, 0, 5000, TEXT("레이저 건")));

	// 상점 구매 아이템
	Add(new ItemData(ITEM_WEAPON, 1005, 100, 0, 0,   0, 0, 50,   TEXT("수류탄")));
	Add(new ItemData(ITEM_WEAPON, 1006, 200, 0, 0,   0, 0, 3000, TEXT("공중 폭격")));
	Add(new ItemData(ITEM_WEAPON, 1007,  30, 0, 0,   0, 0, 1000, TEXT("용암지대")));
	Add(new ItemData(ITEM_HEAL,   1008,   0, 0, 100, 0, 0, 200,  TEXT("벙커 수리")));

	Add(new ItemData(ITEM_BULLET, 1009, 0, 0, 0, 0, 10,  50,  TEXT("권총 탄약")));
	Add(new ItemData(ITEM_BULLET, 1010, 0, 0, 0, 0, 100, 200, TEXT("기관총 탄약")));
	Add(new ItemData(ITEM_BULLET, 1011, 0, 0, 0, 0, 50,  150, TEXT("화염 방사기 기름")));
}

void ItemDB::Add(ItemData* pData)
{
	if (GetData(pData->itemID) == NULL)
	{
		m_pItems[pData->itemID] = pData;
	}
}

ItemData* ItemDB::GetData(int itemID)
{
	if (m_pItems.find(itemID) != m_pItems.end())
	{
		return m_pItems[itemID];
	}
	return NULL;
}