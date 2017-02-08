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
	Item* m_selectedItem;			// 선택한 아이템

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

	virtual void SetCurrentButton(BUTTON_TAG buttonTag) {}


//	virtual Box GetBuyButton() { return m_bBuyButton; }					// 구매 버튼
//	virtual Box GetExitButton() { return m_bExitButton; }				// 나가기 버튼
//	
//	virtual Box GetWeaponButton() { return m_bWeapon; }					// 중분류 : 무기류
//	virtual Box GetBulletButton() { return m_bBullet; }					// 중분류 : 총알류
//	virtual Box GetUsingItemButton() { return m_bUsingItem; }			// 중분류 : 아이템
//	
//	virtual Box GetMachineGunButton() { return m_bMachineGun; }			// 머신건
//	virtual Box GetFireThrowerButton() { return m_bFireThrower; }		// 화염방사기
//	virtual Box GetLaserGunButton() { return m_bLaserGun; }				// 레이저건
//	
//	virtual Box GetPSBulletButton() { return m_bPistolBullet; }			// 권총 탄약
//	virtual Box GetMGBulletButton() { return m_bMachineGunBullet; }		// 머신건 탄약
//	virtual Box GetFTBulletButton() { return m_bFireThrowerBullet; }	// 화염방사기 탄약
//	virtual Box GetLGBulletButton() { return m_bLaserGunBullet; }		// 레이저건 탄약
//	
//	virtual Box GetGrenadeButton() { return m_bGrenade; }				// 수류탄
//	virtual Box GetAirBombButton() { return m_bAirBomb; }				// 공중 폭격
//	virtual Box GetRavaRegionButton() { return m_bRavaRegion; }			// 화염 지대
//	virtual Box GetBunkerRepairButton() { return m_bBunckerRepair; }	// 벙커 수리
//
//	virtual Item* GetSelectedItem() { return m_selectedItem; }	// 선택된 아이템

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