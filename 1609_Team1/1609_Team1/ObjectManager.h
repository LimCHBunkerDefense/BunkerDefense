#pragma once
#include "Singleton.h"
#include "RenderManager.h"
#include "AnimationController.h"
#include <list>
#include "Common.h"
using namespace std;

#define OBJECT ObjectManager::Instance()

class Object
{
	AnimationController* m_pAnim;
	int m_id;
	Vector m_pos;
	Box m_collider;

public:
	Object(int id)
	{
		m_pAnim = new AnimationController();
		m_id = id;
	}

	~Object()
	{
		delete m_pAnim;
	}

	AnimationController* Animation() { return m_pAnim; }
	int ID() { return m_id; }
	Vector Position() { return m_pos; }
	Box Collider() { return m_collider; }

	void SetPosition(Vector pos)
	{
		m_pos = pos;
		m_collider.pos = pos;
	}
	void SetCollider(Vector size, Vector anchor)
	{
		m_collider.size = size;
		m_collider.anchor = anchor;
	}

	virtual void Update(float deltaTime) { }
	virtual void Draw(Camera* pCamera)
	{
		pCamera->DrawRect(m_collider.LeftTop(), m_collider.size);
	}
	virtual void Hit(float damage) { }
};

class ObjectManager : public Singleton<ObjectManager>
{
	Object* m_pPlayer;
	list<Object*> m_propsList;
	list<Object*> m_monsterList;

public:
	void CreatePlayer(Vector pos, Vector colSize, Vector anchor);
	void DestroyPlayer();

	void CreateMonster(int id, Vector pos, Vector colSize, Vector anchor);
	void DestroyAllMonster();

	void CreateProps(int id, Vector pos, Vector colSize, Vector anchor);
	void DestroyProps(Object* pProps);
	void DestroyAllProps();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	Object* GetPlayer() { return m_pPlayer; }

	list<Object*> GetMonsterList() { return m_monsterList; }

	Object* GetProps(int id)
	{
		FOR_LIST(Object*, m_propsList)
		{
			if ((*it)->ID() == id) return (*it);
		}
		return NULL;
	}

	list<Object*> GetPropsList(int id)
	{
		list<Object*> result;
		FOR_LIST(Object*, m_propsList)
		{
			if ((*it)->ID() == id) result.push_back(*it);
		}
		return result;
	}

	list<Object*> GetPropsList() { return m_propsList; }
};

