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
	Add(new ItemData(ITEM_WEAPON, 1001, 10, 0, 5.0f, 0, 50,   0, 0,   TEXT("권총(Pistol)"), 
		TEXT("기본 총이다. \n상점에서 구매할 수 없다.")));
	
	// 상점 구매 무기
	Add(new ItemData(ITEM_WEAPON, 1002, 30, 0, 10.0f, 0, 1000, 0, 2000, TEXT("기관총(Machine Gun)"),
		TEXT("연사가 가능한 기관총. \n시원한 타격감이 일품인 총이다.")));
	Add(new ItemData(ITEM_WEAPON, 1003, 50, 0, 5.0f,  0, 700,  0, 1500, TEXT("화염 방사기(Fire Thrower)"),
		TEXT("근거리에서 사용가능한 화염방사기. \n근거리에서 엄청난 화력을 자랑한다.")));
	Add(new ItemData(ITEM_WEAPON, 1004, 50, 0, 12.0f, 0, 1500, 0, 5000, TEXT("레이저 건(Laser Gun)"), 
		TEXT("엄청난 사거리를 자랑하는 레이저건. \n매우 비싼 가격이지만 눈물을 머금고 구매하기를 강추!")));

	// 상점 구매 아이템(총알)
	Add(new ItemData(ITEM_BULLET, 1005, 0, 0, 0, 0, 0, 10, 50, TEXT("권총 탄약(Pistol Bullet)"),
		TEXT("권총의 탄알집")));
	Add(new ItemData(ITEM_BULLET, 1006, 0, 0, 0, 0, 0, 100, 200, TEXT("기관총 탄약(Machine Gun Bullet)"),
		TEXT("기관총의 탄알집")));
	Add(new ItemData(ITEM_BULLET, 1007, 0, 0, 0, 0, 0, 50, 150, TEXT("화염 방사기 기름(Fire Thr' Oil)"),
		TEXT("화염 방사기 기름")));
	Add(new ItemData(ITEM_BULLET, 1008, 0, 0, 0, 0, 0, 100, 150, TEXT("레이저 건 충전(Laser Gun char')"),
		TEXT("레이저 건 충전")));

	// 상점 구매 아이템(소모품)
	Add(new ItemData(ITEM_USINGITEM, 1009, 100, 0, 5.0f,  0,   0, 0, 50,   TEXT("수류탄(Grenade)"),
		TEXT("가격이 저렴한 수류탄. \n손에 힘이 없어서 멀리는 던지지 못한다.")));
	Add(new ItemData(ITEM_USINGITEM, 1010, 200, 0, 15.0f, 0,   0, 0, 3000, TEXT("공중 폭격(Air Bomb"),
		TEXT("광범위하게 살상하는 공중폭격. \n무전기로 본부를 호출해서 지원을 요청한다.")));
	Add(new ItemData(ITEM_USINGITEM, 1011,  30, 0, 10.0f, 0,   0, 0, 1000, TEXT("용암지대(Rava Region)"),
		TEXT("지속적인 화상상태를 입히는 용암지대. \n용암이 담긴 캡슐을 던져 용암지대를 형성한다.")));
	Add(new ItemData(ITEM_USINGITEM, 1012,   0, 0, 0.0f,  100, 0, 0, 200,  TEXT("벙커 수리(Bunker Repair)"),
		TEXT("금이 간 벙커를 수리. 몬스터로부터 공격당해 금이 간 벙커를 수리한다.")));


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