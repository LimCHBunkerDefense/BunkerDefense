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

	// 오브젝트 충돌체 On/Off
	bool m_colliderOn;

public:
	SceneManager();
	~SceneManager();

	// 씬 등록
	void Register(int tag, IScene* pScene);

	// 씬 반환
	IScene* GetScene(int tag);

	// 씬 변경
	void ChangeScene(int tag);

	// 씬 업데이트
	void Update(float deltaTime);

	// 씬 드로우
	void Draw();

	// 충돌체 On/Off 설정 함수
	void SetColliderOnOff()
	{
		if (m_colliderOn) m_colliderOn = false;
		else m_colliderOn = true;
	}
	// 충돌체 On/Off값 불러오는 함수
	bool GetSetColliderOnOff() { return m_colliderOn; }
};