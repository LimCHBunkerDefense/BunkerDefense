#pragma once
#include "RenderManager.h"
#include "ObjectManager.h"
#include "ItemDB.h"
#include <list>

class Item : public Object
{
	ITEMTYPE_TAG m_iTag;
	ITEM_TAG m_tag;
	int m_itemID;
	int m_money;
	float m_attack;
	float m_defense;
	float m_bunkerLife;
	int m_maxBulletCount;
	int m_reloadBulletCount;
	int m_currentCount;
	int m_maxCount;
	wstring m_name;
	wstring m_info;
	wstring m_range;

	GUN_STATE m_gunState;

public:
	Item();
	Item(int itemID);
	~Item();

	void Update(float deltaTime);
	void Draw();

	// Item Database ¹ÝÈ¯
	int GetID() { return m_itemID; }
	wstring GetName() { return m_name; }
	float GetAttack() { return m_attack; }
	float GetDefense() { return m_defense; }
	float GetBunkerLife() { return m_bunkerLife; }
	int GetMaxBulletCount() { return  m_maxBulletCount; }
	int GetReloadBulletCount() { return m_reloadBulletCount; }
	int GetCurrentCount() { return m_currentCount; }
	void AddCurrentCount(int addCount) { m_currentCount += addCount; }	// ÇöÀç °¹¼ö µ¡¼À ¹× »¬¼À
	int GetMaxCount() { return m_maxCount; }
	wstring GetRange() { return m_range; }
	wstring GetInfo() { return m_info; }
	int GetItemMoney() { return m_money; }
	ITEM_TAG GetTag() { return m_tag; }
	ITEMTYPE_TAG GetItemTypeTag() { return m_iTag; }

	// ÃÑ »óÅÂ ÇÔ¼ö
	void SetGunState(GUN_STATE gunState) { m_gunState = gunState; }
	void IdleState(float deltaTime);
	void ShotState(float deltaTime);
	void ReloadState(float deltaTime);
};

