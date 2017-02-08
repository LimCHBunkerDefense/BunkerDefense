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

	virtual void SetCurrentButton(BUTTON_TAG buttonTag) {}


//	virtual Box GetBuyButton() { return m_bBuyButton; }					// ���� ��ư
//	virtual Box GetExitButton() { return m_bExitButton; }				// ������ ��ư
//	
//	virtual Box GetWeaponButton() { return m_bWeapon; }					// �ߺз� : �����
//	virtual Box GetBulletButton() { return m_bBullet; }					// �ߺз� : �Ѿ˷�
//	virtual Box GetUsingItemButton() { return m_bUsingItem; }			// �ߺз� : ������
//	
//	virtual Box GetMachineGunButton() { return m_bMachineGun; }			// �ӽŰ�
//	virtual Box GetFireThrowerButton() { return m_bFireThrower; }		// ȭ������
//	virtual Box GetLaserGunButton() { return m_bLaserGun; }				// ��������
//	
//	virtual Box GetPSBulletButton() { return m_bPistolBullet; }			// ���� ź��
//	virtual Box GetMGBulletButton() { return m_bMachineGunBullet; }		// �ӽŰ� ź��
//	virtual Box GetFTBulletButton() { return m_bFireThrowerBullet; }	// ȭ������ ź��
//	virtual Box GetLGBulletButton() { return m_bLaserGunBullet; }		// �������� ź��
//	
//	virtual Box GetGrenadeButton() { return m_bGrenade; }				// ����ź
//	virtual Box GetAirBombButton() { return m_bAirBomb; }				// ���� ����
//	virtual Box GetRavaRegionButton() { return m_bRavaRegion; }			// ȭ�� ����
//	virtual Box GetBunkerRepairButton() { return m_bBunckerRepair; }	// ��Ŀ ����
//
//	virtual Item* GetSelectedItem() { return m_selectedItem; }	// ���õ� ������

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