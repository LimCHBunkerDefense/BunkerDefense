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
	//모든 Scene에서 item 정보 접근하기 위해 추가.
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
	bool GetColliderOnOff() { return m_colliderOn; }
};