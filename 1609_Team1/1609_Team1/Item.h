#pragma once

#include "RenderManager.h"
#include "ItemDB.h"

class Item
{
	ITEM_TAG m_tag;
	int m_itemID;
	float m_attack;
	float m_defense;
	int m_quantity;
	wstring m_name;
	Sprite* m_pSprite;
public:
	Item();
	Item(int itemID);
	~Item();
};

