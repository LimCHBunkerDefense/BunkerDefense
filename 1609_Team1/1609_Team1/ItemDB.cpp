#include "ItemDB.h"



ItemDB::ItemDB()
{
}


ItemDB::~ItemDB()
{
}

void ItemDB::Init()
{
	// ±âº» ¹«±â
	Add(new ItemData(ITEM_WEAPON, 1001, 10, 0, 0, 50, 0,   TEXT("±ÇÃÑ")));

	// »óÁ¡ ±¸¸Å ¹«±â
	Add(new ItemData(ITEM_WEAPON, 1002, 30, 0, 0, 1000, 0, TEXT("±â°üÃÑ")));
	Add(new ItemData(ITEM_WEAPON, 1003, 50, 0, 0, 700,  0, TEXT("È­¿° ¹æ»ç±â")));

	// »óÁ¡ ±¸¸Å ¾ÆÀÌÅÛ
	Add(new ItemData(ITEM_WEAPON, 1004, 100, 0, 0, 0, 0,   TEXT("¼ö·ùÅº")));
	Add(new ItemData(ITEM_WEAPON, 1005, 200, 0, 0, 0, 0,   TEXT("°øÁß Æø°Ý")));
	Add(new ItemData(ITEM_WEAPON, 1006,  30, 0, 0, 0, 0,   TEXT("¿ë¾ÏÁö´ë")));
	Add(new ItemData(ITEM_HEAL,   1007,   0, 0, 100, 0, 0, TEXT("º¡Ä¿ ¼ö¸®")));

	Add(new ItemData(ITEM_BULLET, 1008, 0, 0, 0, 0, 10,  TEXT("±ÇÃÑ Åº¾à")));
	Add(new ItemData(ITEM_BULLET, 1009, 0, 0, 0, 0, 100, TEXT("±â°üÃÑ Åº¾à")));
	Add(new ItemData(ITEM_BULLET, 1010, 0, 0, 0, 0, 50,  TEXT("È­¿° ¹æ»ç±â ±â¸§")));
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