#pragma once
#include "RenderManager.h"
#include "ItemDB.h"
#include <list>

class Item
{
	ITEM_TAG m_tag;
	int m_itemID;
	int m_money;
	float m_attack;
	float m_defense;
	float m_bunkerLife;
	int m_bulletCount;
	int m_addBullet;
	wstring m_name;

public:
	Item();
	Item(int itemID);
	~Item();
};

