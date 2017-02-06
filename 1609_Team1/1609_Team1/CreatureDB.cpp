#include "CreatureDB.h"



CreatureDB::CreatureDB()
{
}


CreatureDB::~CreatureDB()
{
}


void CreatureDB::Init()
{
	Add(new CreatureData(1001, 100, 30, TEXT("Ent"))); // ¿¹½Ã
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