#pragma once
#include "Singleton.h"
#include <map>
using namespace std;

#define SCENE SceneManager::Instance()

class IScene
{
public:
	virtual void OnEnter() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnExit() = 0;
	virtual void OnDraw() = 0;
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
	bool GetSetColliderOnOff() { return m_colliderOn; }
};