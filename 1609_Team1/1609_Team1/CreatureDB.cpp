#include "CreatureDB.h"



CreatureDB::CreatureDB()
{
}


CreatureDB::~CreatureDB()
{
}


void CreatureDB::Init()
{
	// 예시 Add(new ItemData(1001, 100, 30, TEXT("ent"), sprite태그));
}

void CreatureDB::Add(CreatureData* pData)
{
	if (GetData(pData->creatureID) == NULL)
	{
		m_pCreatures[pData->creatureID] = pData;
	}
}

CreatureData* CreatureDB::GetData(int creatureID)
{
	if (m_pCreatures.find(creatureID) != m_pCreatures.end())
	{
		return m_pCreatures[creatureID];
	}
	return NULL;
}