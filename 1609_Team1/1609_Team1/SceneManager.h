#pragma once
#include "Singleton.h"
#include "Item.h"
#include "Math.h"
#include <map>
#include <list>

using namespace std;

#define SCENE SceneManager::Instance()

class IScene
{
protected:
	Item* m_selectedItem;			// ������ ������

	list<Box*> m_boxList;			// �ڽ� ����Ʈ
	list<Item*> m_itemList;			// ������ ����Ʈ

public:
	virtual void OnEnter() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnExit() = 0;
	virtual void OnDraw() = 0;

	// ShopScene ��
	virtual list<Box*> GetBoxList() { return m_boxList; }				// �ڽ� ����Ʈ ��ȯ
	virtual void AddBoxList(Box* box) { m_boxList.push_back(box); }		// �ڽ� ����Ʈ �ȿ� �ڽ� �߰�

	virtual list<Item*> GetItemList() { return m_itemList; }

	virtual Item* GetSelectedItem() { return NULL; }					// ������ �����ۿ� ���� �Լ�

	virtual void SetCurrentButton(BUTTON_TAG buttonTag) {}

	virtual void GetIsWeaponClicked() {}								// ������ �ߺз� ��ư�� �������°��� Ȯ���ϴ� GetSet�Լ�
	virtual void SetIsWeaponClicked(bool ON){}
	virtual void GetIsBulletClicked() {}
	virtual void SetIsBulletClicked(bool ON){}
	virtual void GetIsUsingItemClicked() {}
	virtual void SetIsUsingItemClicked(bool ON){} 
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