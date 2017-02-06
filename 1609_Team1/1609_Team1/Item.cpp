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
	m_attack = pData->attack;
	m_defense = pData->defense;
	m_quantity = pData->quantity;
	m_name = pData->name;
}
