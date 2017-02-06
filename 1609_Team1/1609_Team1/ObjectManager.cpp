#include "ObjectManager.h"
#include "Player.h"
#include "Creature.h"

void ObjectManager::Update(float deltaTime)
{
	FOR_LIST(Object*, m_creatureList)
	{
		(*it)->Update(deltaTime);
	}

	//FOR_LIST(Object*, m_bulletList)
	//{
	//	(*it)->Update(deltaTime);
	//}

	//m_pPlayer->Update(deltaTime);
}

void ObjectManager::Draw(Camera* pCamera)
{
	FOR_LIST(Object*, m_creatureList)
	{
		(*it)->Draw(pCamera);
	}

	//FOR_LIST(Object*, m_bulletList)
	//{
	//	(*it)->Draw(pCamera);
	//}

	//m_pPlayer->Draw(pCamera);
}

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

void ObjectManager::DestroyPlayer()
{
	DELETE_OBJECT(m_pPlayer);
}




void ObjectManager::CreateCreature(OBJ_TAG tag, Vector pos, Vector colSize, Vector anchor)
{
	NEW_OBJECT(Object* pCreature, Creature(tag));
	pCreature->SetPosition(pos);
	pCreature->SetCollider(colSize, anchor);

	switch (tag)
	{
	case OBJ_ENT:
		pCreature->Animation()->Register(CREATURE_RUN, new Animation(TEXT("EntRun"), 9, 9, true, 1.0f, anchor.x, anchor.y));
		// pCreture->Animation()->Register(CREATURE_ATTACK, new Animation(TEXT("EntAttack"), 2, 10, false, 2.0f, anchor.x, anchor.y));
		// pCreture->Animation()->Register(CREATURE_DEAD, new Animation(TEXT("EntDead"), 2, 10, false, 2.0f, anchor.x, anchor.y));
		break;
	}	

	m_creatureList.push_back(pCreature);
}
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
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//