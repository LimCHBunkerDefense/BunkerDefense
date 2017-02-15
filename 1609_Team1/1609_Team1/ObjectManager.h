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
	map<int, Object*> m_trashMap;

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

	// ũ������ ��ġ�� �浹ü�� ��ġ�� ���ÿ� �ٲٱ� ���� �߰��� �Լ�
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



	// ũ���� ������ ���� �Լ�
	void SetScale(float scale)
	{
		m_pAnim->Current()->GetSprite()->SetScale(scale);
	}

	// �׽�Ʈ�� ������ ��ȯ �Լ�
	float GetScale() { return m_pAnim->Current()->GetSprite()->GetScale(); }

	virtual void Update(float deltaTime) { }
	virtual void Draw(Camera* pCamera)
	{
		pCamera->DrawRect(m_collider.LeftTop(), m_collider.size);
	}

	// ũ���Ŀ� �Լ�
	virtual void SetMoveDirection(Vector moveDirection) {}
	virtual Vector GetMoveDirection() { return Vector::Zero(); }
	virtual void SetStartPos(Vector pos) { }
	virtual Vector GetStartPos() { return Vector::Zero(); }
	virtual float GetMT() { return 0; }
	virtual float GetCollideAngle() { return 0; }

	//Bullet�� �Լ�
	virtual BOOL UpdateBool(float deltaTime) { return false; }

	// �����ۿ� �Լ�
	virtual int GetID() { return NULL; }
	virtual wstring GetName() { return NULL; }
	virtual float GetAttack() { return NULL; }
	virtual float GetDefense() { return NULL; }		// ��Ŀ������ �����
	virtual float GetBunkerLife() { return NULL; }
	virtual int GetMaxBulletCount() { return  NULL; }
	virtual int GetReloadBulletCount() { return NULL; }
	virtual int GetCurrentCount() { return NULL; }
	virtual void AddCurrentCount(int addCount) {}
	virtual int GetMaxCount() { return NULL; }
	virtual wstring GetRange() { return NULL; }
	virtual wstring GetInfo() { return NULL; }
	virtual int GetItemMoney() { return NULL; }
	virtual ITEM_TAG GetTag() { return ITEM_NONE; }
	virtual ITEMTYPE_TAG GetItemTypeTag() { return ITEMTYPE_NONE; }

	//Player
	virtual ITEM_TAG GetItemState() { return ITEM_NONE; }
	virtual map<int, Object*> GetItemBag() { return m_trashMap; }

	// ��Ŀ�� �Լ�
	virtual float GetCurrentLife() { return NULL; }
	virtual void AddCurrentLife(float addLife) {}
	virtual float GetMaxLife() { return NULL;}
	virtual void AddMaxLife(float addLife) {  }
	virtual void AddDefense(float addDefense) {}

};

class ObjectManager : public Singleton<ObjectManager>
{
	float m_deltaSightAngle;
	float m_deltaSightHeight;
	float m_sightHeight;

	Vector m_aim;						// �÷��̾� ������ ��ǥ

	Object* m_pPlayer;
	Object* m_bunker;
	list<Object*> m_creatureList;
	list<Object*> m_bulletList;
	list<Object*> m_shopItemList;				// ������ ������ ����Ʈ


public:	
	ObjectManager();
	~ObjectManager();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	// �÷��̾�
	void CreatePlayer(Vector pos, Vector colSize, Vector anchor);
	Object* GetPlayer() { return m_pPlayer; }
	void DestroyPlayer();
	
	// ũ����
	void CreateCreature(OBJ_TAG tag, Vector pos);
	list<Object*> GetCreatureList() { return m_creatureList; }
	void DestroyCreature(Object* pCreature);
	void DestroyAllCreature();

	// ������
	Object* CreateItem(ITEM_TAG tag, int itemID);
	list<Object*> GetShopItemList() { return m_shopItemList; }



	// �Ѿ�
	void CreateBullet(OBJ_TAG tag, Vector pos);
	list<Object*> GetBulletList() { return m_bulletList; }
	void DestroyBullet(Object* pCreature);
	void DestroyAllBullet();

	// ��Ŀ
	void CreateBunker();
	void DestroyBunker();
	Object* GetBunker() { return m_bunker; }
	

	// ī�޶� ȸ���� ���� ũ���� �� �ҷ��� ��ġ ����
	void SetPosByDeltaAngle(float deltaTime);


	// �÷��̾��� ���콺 ȸ���� ���� �� ��ȭ�� ���� �� ȣ��
	void SetDeltaSightAngle(float deltaAngle) { m_deltaSightAngle = deltaAngle; }
	float GetDeltaSightAngle() { return m_deltaSightAngle; }
	void SetDeltaSightHeight(float deltaHeight) { m_deltaSightHeight = deltaHeight; }
	float GetDeltaSightHeight() { return m_deltaSightHeight; }

	void SetSightHeight(float height) { m_sightHeight = MATH->Clamp(height + m_sightHeight, SIGHTHEIGHT_MIN, SIGHTHEIGHT_MAX); }
	float GetSightHeight() { return m_sightHeight; }

	// �÷��̾� ���� ��ǥ ����
	Vector GetAimPos() { return m_aim; }
	void SetAimPos(Vector aim)
	{ 
		float y = MATH->Clamp(aim.y, SIGHTHEIGHT_MIN, SIGHTHEIGHT_MAX);
		m_aim = Vector(aim.x, y); 
	}
};

