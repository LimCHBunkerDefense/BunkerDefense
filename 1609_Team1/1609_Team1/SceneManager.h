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
	Item* m_selectedItem;			// 구매한 아이템

	list<Box*> m_boxList;			// 박스 리스트
	list<Item*> m_itemList;			// 아이템 리스트

public:
	virtual void OnEnter() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnExit() = 0;
	virtual void OnDraw() = 0;

	// ShopScene 용
	virtual list<Box*> GetBoxList() { return m_boxList; }				// 박스 리스트 반환
	virtual void AddBoxList(Box* box) { m_boxList.push_back(box); }		// 박스 리스트 안에 박스 추가

	virtual list<Item*> GetItemList() { return m_itemList; }

	virtual Item* GetSelectedItem() { return NULL; }					// 구매한 아이템에 대한 함수

	virtual void SetCurrentButton(BUTTON_TAG buttonTag) {}

	virtual void GetIsWeaponClicked() {}								// 아이템 중분류 버튼이 눌러졌는가를 확인하는 GetSet함수
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