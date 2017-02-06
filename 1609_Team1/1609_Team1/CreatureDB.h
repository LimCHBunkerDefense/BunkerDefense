#pragma once

#include "Singleton.h"
#include "Common.h"
#include "Math.h"
#include "RenderManager.h"
#include <map>

#define CREATURE CreatureDB::Instance()

struct CreatureData
{
	int creatureID;
	float attack;
	float defense;
	wstring name;

public:
	CreatureData(int creatureID, float attack, float defense, wstring name)
	{
		this->creatureID = creatureID;
		this->attack = attack;
		this->defense = defense;
		this->name = name;

	}

};

class CreatureDB : public Singleton<CreatureDB>
{
	map<int, CreatureData*> m_pCreatures;
public:
	CreatureDB();
	~CreatureDB();

	void Init();
	void Add(CreatureData* pData);
	CreatureData* GetData(int creatureID);
};

