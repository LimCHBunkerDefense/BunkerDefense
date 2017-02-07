#include "CreatureDB.h"



CreatureDB::CreatureDB()
{
}


CreatureDB::~CreatureDB()
{
}


void CreatureDB::Init()
{
	Add(new CreatureData(OBJ_ENT, 100, 100, 30, TEXT("Ent"), 5.5f)); // ¿¹½Ã
}

void CreatureDB::Add(CreatureData* pData)
{
	if (GetData(pData->tag) == NULL)
	{
		m_pCreatures[pData->tag] = pData;
	}
}

CreatureData* CreatureDB::GetData(OBJ_TAG tag)
{
	if (m_pCreatures.find(tag) != m_pCreatures.end())
	{
		return m_pCreatures[tag];
	}
	return NULL;
}