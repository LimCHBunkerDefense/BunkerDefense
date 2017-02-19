#pragma once
#include "Singleton.h"
#include "Common.h"
#include "Math.h"
#include "RenderManager.h"
#include <map>

#define ITEM ItemDB::Instance()

struct ItemData
{
	ITEMTYPE_TAG iTag;			// �ߺз� ������ �±� 
	ITEM_TAG tag;				// �Һз� ������ �±�
	int itemID;					// �����ۿ� ���� ID��
	int money;					// ������ ���ſ� �ʿ��� ��
	float attack;				// �ɷ�ġ - ���ݷ�	
	float range;				// �ɷ�ġ - �����Ÿ�
	float repair;					// ������
	float bulletSpeed;			// �Ѿ� �ӵ�
	float bunkerLife;			// ��Ŀ ü��
	int maxBulletCount;			// �ѿ� �����ϴ� �Ѿ��� ����
	int reloadBulletCount;		// ������ �� �ִ� �Ѿ��� ����
	int maxCount;				// �������� ������ �� �ִ� �ִ� ����
	wstring name;				// ������ �̸�
	wstring info;				// ������ ����
	wstring ragestr;			// �����Ÿ� ǥ�� �̸�
		
	ItemData(ITEMTYPE_TAG iTag, ITEM_TAG tag, int itemID, float attack, float range, float repair, float bulletSpeed,
		float bunkerLife, int maxBulletCount, int reloadBulletCount, int maxCount, int money, 
		wstring name, wstring info, wstring ragestr = TEXT(" "))
	{
		this->iTag = iTag;
		this->tag = tag;
		this->itemID = itemID;
		this->attack = attack;
		this->range = range;
		this->repair = repair;
		this->bulletSpeed = bulletSpeed;
		this->bunkerLife = bunkerLife;
		this->maxBulletCount = maxBulletCount;
		this->reloadBulletCount = reloadBulletCount;
		this->maxCount = maxCount;
		this->money = money;
		this->name = name;
		this->info = info;
		this->ragestr = ragestr;
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
	int GetItem(int itemID) { return itemID; }
	ItemData* GetData(int itemID);
};

