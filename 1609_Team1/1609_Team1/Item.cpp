#include "Item.h"



Item::Item()
{
}


Item::~Item()
{
}

Item::Item(int itemID)
{
	ItemData* pData = ITEM->GetData(itemID);

	m_tag = pData->tag;
	m_itemID = pData->itemID;
	m_money = pData->money;
	m_attack = pData->attack;
	m_defense = pData->defense;
	m_bunkerLife = pData->bunkerLife;
	m_bulletCount = pData->bulletCount;
	m_addBullet = pData->addBullet;
	m_name = pData->name;
}

