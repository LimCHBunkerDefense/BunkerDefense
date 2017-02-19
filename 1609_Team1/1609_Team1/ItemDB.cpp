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
	Add(new ItemData(ITEMTYPE_WEAPON, ITEM_PISTOL, 1001, 10, 60.0f, 0, 20.0f, 0, 60, 10,   1, 0,   TEXT("권총(Pistol)"),
		TEXT("기본 총이다. \n상점에서 구매할 수 없다."), TEXT("하")));
	
	// 상점 구매 무기
	Add(new ItemData(ITEMTYPE_WEAPON, ITEM_SHOTGUN, 1002, 80, 50.0f, 0, 25.0f, 0, 24, 2, 1, 1200, TEXT("샷건(Shot Gun)"),
		TEXT("근거리에서 사용가능한 샷건. \n근거리에서 엄청난 화력을 자랑한다."), TEXT("하")));
	Add(new ItemData(ITEMTYPE_WEAPON, ITEM_MACHINEGUN, 1003, 30,100.0f, 0, 50.0f, 0, 2000, 500, 1, 2000, TEXT("기관총(Machine Gun)"),
		TEXT("연사가 가능한 기관총. \n시원한 타격감이 일품인 총이다."), TEXT("중")));
	Add(new ItemData(ITEMTYPE_WEAPON, ITEM_LASERGUN, 1004, 50, 120.0f, 0, 40.0f, 0, 2000, 1000, 1, 5000, TEXT("레이저 건(Laser Gun)"),
		TEXT("엄청난 사거리를 자랑하는 레이저건. \n매우 비싼 가격이지만 눈물을 머금고\n 구매하기를 강추!"), TEXT("최상")));

	// 상점 구매 아이템(총알)
	Add(new ItemData(ITEMTYPE_BULLET, ITEM_PSBULLET, 2001, 0, 0, 0, 0, 0, 0, 0, 60, 10, TEXT("권총 탄약(Pistol Bullet)"),
		TEXT("권총의 탄약")));
	Add(new ItemData(ITEMTYPE_BULLET, ITEM_SGBULLET, 2002, 0, 0, 0, 0, 0, 0, 0, 1800, 20, TEXT("샷건 탄약(Shot Gun Bullet)"),
		TEXT("샷건 탄약")));
	Add(new ItemData(ITEMTYPE_BULLET, ITEM_MGBULLET, 2003, 0, 0, 0, 0, 0, 0, 0, 2000, 15, TEXT("기관총 탄약(Machine Gun Bullet)"),
		TEXT("기관총의 탄약")));
	Add(new ItemData(ITEMTYPE_BULLET, ITEM_LGBULLET, 2004, 0, 0, 0, 0, 0, 0, 0, 2000, 30, TEXT("레이저 건 충전(Laser Gun char')"),
		TEXT("레이저 건 충전")));
	 
	// 상점 구매 아이템(소모품)
	Add(new ItemData(ITEMTYPE_USINGITEM, ITEM_GRENADE, 3001, 100, 50.0f, 0, 25.0f, 0,   0, 0, 10, 50,   TEXT("수류탄(Grenade)"),
		TEXT("가격이 저렴한 수류탄. \n손에 힘이 없어서 멀리는 던지지 못한다."), TEXT("중상")));
	Add(new ItemData(ITEMTYPE_USINGITEM, ITEM_AIRBOMB, 3002, 200,  120.0f, 0, 60.0f, 0,   0, 0, 3, 3000, TEXT("공중 폭격(Air Bomb)"),
		TEXT("광범위하게 살상하는 공중폭격. \n무전기로 본부를 호출해서 지원을\n 요청한다."), TEXT("최상")));
	Add(new ItemData(ITEMTYPE_USINGITEM, ITEM_FIRECAPSULE, 3003,  30, 50.0f, 0, 25.0f, 0,   0, 0, 5, 1000, TEXT("화염 캡슐(Fire Capsule)"),
		TEXT("지속적인 화상상태를 입히는 화염캡슐. \n캡슐이 땅에 떨어지는 순간 화학 작용으로 \n 화염 지대를 형성한다."), TEXT("중상")));
	Add(new ItemData(ITEMTYPE_USINGITEM, ITEM_BUNKERREPAIR, 3004, 0, 0, 200.0f, 0.0f, 100, 0, 0, 10, 200,  TEXT("벙커 수리(Bunker Repair)"),
		TEXT("금이 간 벙커를 수리. \n몬스터로부터 공격당해 금이 간 벙커를 수리\n 한다.")));
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