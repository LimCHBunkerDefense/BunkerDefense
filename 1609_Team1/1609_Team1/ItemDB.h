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
	float attack;
	float defense;
	int quantity;
	wstring name;
	Sprite* pSprite;

	ItemData(ITEM_TAG tag, int itemID, float attack, float defense, wstring name, Sprite* pSprite)
	{
		this->tag = tag;
		this->itemID = itemID;
		this->attack = attack;
		this->defense = defense;
		this->pSprite = pSprite;

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

