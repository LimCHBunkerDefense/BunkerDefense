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
	OBJ_TAG m_tag;
	Vector m_pos;
	Box m_collider;

public:
	Object() {}
	Object(OBJ_TAG tag)
	{
		m_pAnim = new AnimationController();
		m_tag = tag;
	}

	~Object()
	{
		delete m_pAnim;
	}

	AnimationController* Animation() { return m_pAnim; }
	OBJ_TAG Tag() { return m_tag; }
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
};

class ObjectManager : public Singleton<ObjectManager>
{
	Object* m_pPlayer;
	Object* m_bunker;
	list<Object*> m_creatureList;
	list<Object*> m_bulletList;

public:	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void CreatePlayer(Vector pos, Vector colSize, Vector anchor);
	Object* GetPlayer() { return m_pPlayer; }
	void DestroyPlayer();
	
	void CreateCreature(OBJ_TAG tag, Vector pos, Vector colSize, Vector anchor = Vector(0.5f, 1.0f));
	//void DestroyAllCreature();
	//
	//
	//
	//
	//Object* GetPlayer() { return m_pPlayer; }
	//
	//list<Object*> GetCreatureList() { return m_creatureList; }
	//
	//Object* GetProps(int id)
	//{
	//	FOR_LIST(Object*, m_propsList)
	//	{
	//		if ((*it)->ID() == id) return (*it);
	//	}
	//	return NULL;
	//}
	//
	//list<Object*> GetPropsList(int id)
	//{
	//	list<Object*> result;
	//	FOR_LIST(Object*, m_propsList)
	//	{
	//		if ((*it)->ID() == id) result.push_back(*it);
	//	}
	//	return result;
	//}
	//
	//list<Object*> GetBulletList() { return m_bulletList; }
};

