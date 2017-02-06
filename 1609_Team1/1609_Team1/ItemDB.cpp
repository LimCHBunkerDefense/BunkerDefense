#include "ItemDB.h"



ItemDB::ItemDB()
{
}


ItemDB::~ItemDB()
{
}

void ItemDB::Init()
{
	// 예시 Add(new ItemData(ITEM_WEAPON, 1001, 10, 0, TEXT("machinegun"), sprite태그));
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