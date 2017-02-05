#include "ObjectManager.h"
#include "Player.h"
#include "Creature.h"

//void ObjectManager::CreatePlayer(Vector pos, Vector colSize, Vector anchor)
//{
//	NEW_OBJECT(m_pPlayer, Player(OBJ_PLAYER));
//	m_pPlayer->SetPosition(pos);
//	m_pPlayer->SetCollider(colSize, anchor);
//	//m_pPlayer->Animation()->Register(CHARACTER_IDLE,
//	//	new Animation(TEXT("Idle"), 6, 10, true, 2.0f, anchor.x, anchor.y));
//	//m_pPlayer->Animation()->Register(CHARACTER_RUN,
//	//	new Animation(TEXT("Run"), 8, 10, true, 2.0f, anchor.x, anchor.y));
//	//m_pPlayer->Animation()->Register(CHARACTER_PUNCH,
//	//	new Animation(TEXT("Punch"), 6, 30, false, 2.0f, anchor.x, anchor.y));
//	//m_pPlayer->Animation()->Register(CHARACTER_JUMP,
//	//	new Animation(TEXT("Jump"), 1, 10, true, 2.0f, anchor.x, anchor.y));
//	//m_pPlayer->Animation()->Register(CHARACTER_HIT,
//	//	new Animation(TEXT("Hit"), 2, 10, false, 2.0f, anchor.x, anchor.y));
//}
//
//void ObjectManager::DestroyPlayer()
//{
//	DELETE_OBJECT(m_pPlayer);
//}
//
//void ObjectManager::CreateCreature(int id, Vector pos, Vector colSize, Vector anchor)
//{
//	NEW_OBJECT(Object* monster, Monster(id));
//	monster->SetPosition(pos);
//	monster->SetCollider(colSize, anchor);
//
//	monster->Animation()->Register(CHARACTER_IDLE,
//		new Animation(TEXT("Idle"), 6, 10, true, 2.0f, anchor.x, anchor.y));
//	monster->Animation()->Register(CHARACTER_HIT,
//		new Animation(TEXT("Hit"), 2, 10, false, 2.0f, anchor.x, anchor.y));
//
//	m_monsterList.push_back(monster);
//}
//
//void ObjectManager::DestroyAllCreature()
//{
//	FOR_LIST(Object*, m_monsterList)
//	{
//		DELETE_OBJECT((*it));
//	}
//	m_creatureList.clear();
//}
//
//void ObjectManager::Update(float deltaTime)
//{
//	FOR_LIST(Object*, m_creatureList)
//	{
//		(*it)->Update(deltaTime);
//	}
//
//	FOR_LIST(Object*, m_bulletList)
//	{
//		(*it)->Update(deltaTime);
//	}
//
//	m_pPlayer->Update(deltaTime);
//}
//
//void ObjectManager::Draw(Camera* pCamera)
//{
//	FOR_LIST(Object*, m_propsList)
//	{
//		(*it)->Draw(pCamera);
//	}
//
//	FOR_LIST(Object*, m_monsterList)
//	{
//		(*it)->Draw(pCamera);
//	}
//
//	m_pPlayer->Draw(pCamera);
//}


//02-04 02:52 ÀÌ½Â¹® ¼öÁ¤
void ObjectManager::CreatePlayer(Vector pos, Vector colSize, Vector anchor)
{
	NEW_OBJECT(m_pPlayer, Player(OBJ_PLAYER));
	m_pPlayer->SetPosition(pos);
	m_pPlayer->SetCollider(colSize, anchor);
	//m_pPlayer->Animation()->Register(CHARACTER_IDLE,
	//	new Animation(TEXT("Idle"), 6, 10, true, 2.0f, anchor.x, anchor.y));
	//m_pPlayer->Animation()->Register(CHARACTER_RUN,
	//	new Animation(TEXT("Run"), 8, 10, true, 2.0f, anchor.x, anchor.y));
	//m_pPlayer->Animation()->Register(CHARACTER_PUNCH,
	//	new Animation(TEXT("Punch"), 6, 30, false, 2.0f, anchor.x, anchor.y));
	//m_pPlayer->Animation()->Register(CHARACTER_JUMP,
	//	new Animation(TEXT("Jump"), 1, 10, true, 2.0f, anchor.x, anchor.y));
	//m_pPlayer->Animation()->Register(CHARACTER_HIT,
	//	new Animation(TEXT("Hit"), 2, 10, false, 2.0f, anchor.x, anchor.y));
}

void ObjectManager::Draw(Camera* pCamera)
{

	m_pPlayer->Draw(pCamera);
}