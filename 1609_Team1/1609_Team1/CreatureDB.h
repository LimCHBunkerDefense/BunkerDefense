#pragma once

#include "Singleton.h"
#include "Common.h"
#include "Math.h"
#include "RenderManager.h"
#include <map>

#define CREATURE CreatureDB::Instance()

struct CreatureData
{
	OBJ_TAG tag;
	float life;
	float attack;
	float defense;
	wstring name;
	float attackSpeed;	//	(attackSpeed)초에 한 번씩 공격함
	float moveSpeed;
	int money;
	int score;

public:
	CreatureData(OBJ_TAG tag, float life, float attack, float defense, wstring name, float attackSpeed, float moveSpeed, int money, int score)
	{
		this->tag = tag;
		this->life = life;
		this->attack = attack;
		this->defense = defense;
		this->name = name;
		this->attackSpeed = attackSpeed;
		this->moveSpeed = moveSpeed;
		this->money = money;
		this->score = score;
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
	CreatureData* GetData(OBJ_TAG tag);
};

