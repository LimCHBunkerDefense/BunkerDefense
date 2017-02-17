#include "CreatureDB.h"



CreatureDB::CreatureDB()
{
}


CreatureDB::~CreatureDB()
{
}


void CreatureDB::Init()
{
	Add(new CreatureData(OBJ_LAVA, 100, 5, 5, TEXT("Lava"), 1.5, 0.08, 100, 50));
	// Add(new CreatureData(OBJ_2단계, 200, 100, 30, TEXT("Ent"), 3.0f, 0.5, 500, 200)); 
	// Add(new CreatureData(OBJ_3단계, 400, 100, 30, TEXT("Ent"), 3.0f, 0.5, 500, 200)); 
	Add(new CreatureData(OBJ_ENT, 800, 15, 30, TEXT("Ent"), 3.0f, 0.03, 500, 200)); 
	Add(new CreatureData(OBJ_DARKPRIEST, 3000, 50, 100, TEXT("DarkPriest"), 3.0f, 0.08, 10000, 10000)); 
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