#pragma once
#include "Singleton.h"
#include "Common.h"
#include "Math.h"
#include "RenderManager.h"
#include <map>

#define ITEM ItemDB::Instance()

struct ItemData
{
	ITEM_TAG tag;
	int itemID;
	int money;
	float attack;
	float defense;
	float bunkerLife;
	int bulletCount;
	int addBullet;
	int quantity;
	wstring name;

	ItemData(ITEM_TAG tag, int itemID, float attack, float defense, float bunkerLife, int bulletCount, int addBullet, int money, wstring name)
	{
		this->tag = tag;
		this->itemID = itemID;
		this->attack = attack;
		this->defense = defense;
		this->bunkerLife = bunkerLife;
		this->bulletCount = bulletCount;
		this->addBullet = addBullet;
	}


public:

};


class ItemDB : public Singleton<ItemDB>
{
	map<int, ItemData*> m_pItems;
public:
	ItemDB();
	~ItemDB();

	void Init();
	void Add(ItemData* pData);
	ItemData* GetData(int itemID);
};

