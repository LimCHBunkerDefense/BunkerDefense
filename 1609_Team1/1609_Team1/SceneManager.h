#pragma once
#include "Singleton.h"
#include "ObjectManager.h"
#include "item.h"
#include "Math.h"
#include <map>
#include <list>

using namespace std;

#define SCENE SceneManager::Instance()

class IScene
{
protected:
	Object* m_selectedItem;			// ������ ������

	list<Box*> m_boxList;			// �ڽ� ����Ʈ

public:
	virtual void OnEnter() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnExit() = 0;
	virtual void OnDraw() = 0;

	// ShopScene ��
	virtual list<Box*> GetBoxList() { return m_boxList; }				// �ڽ� ����Ʈ ��ȯ
	virtual void AddBoxList(Box* box) { m_boxList.push_back(box); }		// �ڽ� ����Ʈ �ȿ� �ڽ� �߰�

	virtual Object* GetSelectedItem() { return NULL; }					// ������ �����ۿ� ���� �Լ�
	virtual void SetSelectedItem(int itemID) {}
	virtual void SetCurrentButton(BUTTON_TAG buttonTag) {}
	virtual int GetCurrentButton() { return NULL; }

	virtual bool GetIsWeaponClicked() { return NULL; }					// ������ �ߺз� ��ư�� �������°��� Ȯ���ϴ� GetSet�Լ�
	virtual void SetIsWeaponClicked(bool ON){}
	virtual bool GetIsBulletClicked() { return NULL; }
	virtual void SetIsBulletClicked(bool ON){}
	virtual bool GetIsUsingItemClicked() { return NULL; }
	virtual void SetIsUsingItemClicked(bool ON){} 
	virtual bool GetBuyClicked() { return NULL; }
	virtual void SetBuyCilcked(bool ON) {}

	virtual int GetInputCount() { return NULL; }
	virtual void SetInputCount(int addCount) {}
	virtual bool GetInputOnOff() { return NULL; }
	virtual void SetInputOnOff(bool ON) {}

	// PlayScene ��
	virtual void SetPosBg(Vector pos) {}
	virtual Vector GetPosBg() { return Vector::Zero(); }
};

class SceneManager : public Singleton<SceneManager>
{
	map<int, IScene*> m_scenes;
	int m_current;

	// ������Ʈ �浹ü On/Off
	bool m_colliderOn;

public:
	SceneManager();
	~SceneManager();

	// �� ���
	void Register(int tag, IScene* pScene);

	// �� ��ȯ
	IScene* GetScene(int tag);

	// �� ����
	void ChangeScene(int tag);

	// �� ������Ʈ
	void Update(float deltaTime);

	// �� ��ο�
	void Draw();

	// �浹ü On/Off ���� �Լ�
	void SetColliderOnOff()
	{
		if (m_colliderOn) m_colliderOn = false;
		else m_colliderOn = true;
	}
	// �浹ü On/Off�� �ҷ����� �Լ�
	bool GetColliderOnOff() { return m_colliderOn; }
};