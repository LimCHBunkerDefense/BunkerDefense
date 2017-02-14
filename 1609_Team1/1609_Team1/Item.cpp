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

	m_iTag = pData->iTag;
	m_tag = pData->tag;
	m_itemID = pData->itemID;
	m_money = pData->money;
	m_attack = pData->attack;
	m_defense = pData->defense;
	m_bunkerLife = pData->bunkerLife;
	m_maxBulletCount = pData->maxBulletCount;
	m_reloadBulletCount = pData->reloadBulletCount;
	m_maxCount = pData->maxCount;
	m_name = pData->name;
	m_info = pData->info;
}

void Item::Update(float deltaTime)
{
	switch (m_gunState)
	{
	case GUN_IDLE: IdleState(deltaTime); break;
	case GUN_SHOT: ShotState(deltaTime); break;
	case GUN_RELOAD: ReloadState(deltaTime); break;
	}
	
	Animation()->Update(deltaTime);
}

void Item::Draw()
{

}

void Item::IdleState(float deltaTime)
{
	Animation()->Play(GUN_IDLE);
}

void Item::ShotState(float deltaTime)
{
	Animation()->Play(GUN_SHOT);
}

void Item::ReloadState(float deltaTime)
{
	Animation()->Play(GUN_RELOAD);
}