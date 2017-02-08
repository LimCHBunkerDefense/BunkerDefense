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
	Box m_box;
	//��� Scene���� item ���� �����ϱ� ���� �߰�.
protected:
	list<Item*> m_itemList;

public:
	virtual void OnEnter() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnExit() = 0;
	virtual void OnDraw() = 0;

	virtual Box GetButton() { return m_box; }
	virtual Item* SelectItem(	) { return NULL; }
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