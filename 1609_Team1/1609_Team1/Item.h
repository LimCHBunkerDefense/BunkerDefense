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
	wstring m_info;

public:
	Item();
	Item(int itemID);
	~Item();
	
	wstring GetName() { return m_name; }
	wstring GetInfo() { return m_info; }
	ITEM_TAG GetTag() { return m_tag; }
};

