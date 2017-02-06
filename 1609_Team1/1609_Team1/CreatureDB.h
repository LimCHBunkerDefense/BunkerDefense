#pragma once

#include "Singleton.h"
#include "Common.h"
#include "Math.h"
#include "RenderManager.h"
#include <map>

struct CreatureData
{
	int creatureID;
	float attack;
	float defense;
	wstring name;
	Sprite* pSprite;

public:
	CreatureData(int creatureID, float attack, float defense, wstring name, Sprite* pSprite)
	{
		this->creatureID = creatureID;
		this->attack = attack;
		this->defense = defense;
		this->name = name;
		this->pSprite = pSprite;

	}

};

class CreatureDB
{
	map<int, CreatureData*> m_pCreatures;
public:
	CreatureDB();
	~CreatureDB();

	void Init();
	void Add(CreatureData* pData);
	CreatureData* GetData(int creatureID);
};

