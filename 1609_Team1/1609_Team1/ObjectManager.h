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
	void SetAnimation(AnimationController* anim) { m_pAnim = anim; }
	OBJ_TAG Tag() { return m_tag; }
	Vector Position() { return m_pos; }
	Box Collider() { return m_collider; }

	


	void SetPosition(Vector pos)
	{
		m_pos = pos;
		m_collider.pos = pos;
	}

	// 크리쳐의 위치와 충돌체의 위치를 동시에 바꾸기 위해 추가한 함수
	void SetPosition_Creature(Vector pos, Vector colPos)
	{
		m_pos = pos;
		m_collider.pos = colPos;
	}

	void SetCollider(Vector size, Vector anchor)
	{
		m_collider.size = size;
		m_collider.anchor = anchor;
	}



	// 크리쳐 스케일 조정 함수
	void SetScale(float scale)
	{
		m_pAnim->Current()->GetSprite()->SetScale(scale);
	}

	// 테스트용 스케일 반환 함수
	float GetScale() { return m_pAnim->Current()->GetSprite()->GetScale(); }

	virtual void Update(float deltaTime) { }
	virtual void Draw(Camera* pCamera)
	{
		pCamera->DrawRect(m_collider.LeftTop(), m_collider.size);
	}

	// 크리쳐용 함수
	virtual void SetMoveDirection(Vector moveDirection) {}
	virtual Vector GetMoveDirection() { return Vector::Zero(); }
	virtual void SetStartPos(Vector pos) { }
	virtual Vector GetStartPos() { return Vector::Zero(); }
	virtual float GetMT() { return 0; }
	virtual float GetCollideAngle() { return 0; }

	//Bullet용 함수
	virtual BOOL UpdateBool(float deltaTime) { return false; }



};

class ObjectManager : public Singleton<ObjectManager>
{
	float m_deltaSightAngle;
	float m_deltaSightHeight;
	float m_sightHeight;

	Vector m_aim;						// 플레이어 조준점 좌표

	Object* m_pPlayer;
	Object* m_bunker;
	list<Object*> m_creatureList;
	list<Object*> m_bulletList;


public:	
	ObjectManager();
	~ObjectManager();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	// 플레이어
	void CreatePlayer(Vector pos, Vector colSize, Vector anchor);
	Object* GetPlayer() { return m_pPlayer; }
	void DestroyPlayer();
	
	// 크리쳐
	void CreateCreature(OBJ_TAG tag, Vector pos);
	list<Object*> GetCreatureList() { return m_creatureList; }

	void DestroyCreature(Object* pCreature)
	{
		m_creatureList.remove(pCreature);
		DELETE_OBJECT(pCreature);
	}

	void DestroyAllCreature()
	{
		FOR_LIST(Object*, m_creatureList)
		{
			DELETE_OBJECT((*it));
		}
		m_creatureList.clear();
	}

	// 아이템
	void CreateItem(GUN_TAG, int itemID);


	// 총알
	void CreateBullet(OBJ_TAG tag, Vector pos);
	list<Object*> GetBulletList() {	return m_bulletList; }
	
	void DestroyBullet(Object* pCreature)
	{
		m_bulletList.remove(pCreature);
		DELETE_OBJECT(pCreature);
	}

	void DestroyAllBullet()
	{
		FOR_LIST(Object*, m_bulletList)
		{
			DELETE_OBJECT((*it));
		}
		m_bulletList.clear();
	}
	

	// 카메라 회전에 따른 크리쳐 및 불렛의 위치 조정
	void SetPosByDeltaAngle();


	// 플레이어의 마우스 회전에 의한 각 변화값 저장 및 호출
	void SetDeltaSightAngle(float deltaAngle) { m_deltaSightAngle = deltaAngle; }
	float GetDeltaSightAngle() { return m_deltaSightAngle; }
	void SetDeltaSightHeight(float deltaHeight) { m_deltaSightHeight = deltaHeight; }
	float GetDeltaSightHeight() { return m_deltaSightHeight; }
	void SetSightHeight(float height) { m_sightHeight = height; }
	float GetSightHeight() { return m_sightHeight; }

	// 플레이어 에임 좌표 관련
	Vector GetAimPos() { return m_aim; }
	void SetAimPos(Vector aim) { m_aim = aim; }
};

