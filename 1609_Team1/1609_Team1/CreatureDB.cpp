#include "CreatureDB.h"



CreatureDB::CreatureDB()
{
}


CreatureDB::~CreatureDB()
{
}


void CreatureDB::Init()
{
	// Add(new CreatureData(OBJ_1단계, 100, 100, 30, TEXT("Ent"), 3.0f, 0.5, 500, 200)); 
	// Add(new CreatureData(OBJ_2단계, 200, 100, 30, TEXT("Ent"), 3.0f, 0.5, 500, 200)); 
	// Add(new CreatureData(OBJ_3단계, 400, 100, 30, TEXT("Ent"), 3.0f, 0.5, 500, 200)); 
	Add(new CreatureData(OBJ_ENT, 800, 100, 30, TEXT("Ent"), 3.0f, 0.05, 500, 200)); 
	// Add(new CreatureData(OBJ_대빵, 3000, 100, 30, TEXT("Ent"), 3.0f, 0.5, 500, 200)); 
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