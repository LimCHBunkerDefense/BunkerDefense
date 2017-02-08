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
	wstring m_range;

public:
	Item();
	Item(int itemID);
	~Item();
	
	int GetID() { return m_itemID; }
	wstring GetName() { return m_name; }
	float GetAttack() { return m_attack; }
	float GetDefense() { return m_defense; }
	float GetBunkerLife() { return m_bunkerLife; }
	wstring GetRange() { return m_range; }
	wstring GetInfo() { return m_info; }
	int GetItemMoney() { return m_money; }
	ITEM_TAG GetTag() { return m_tag; }
};

