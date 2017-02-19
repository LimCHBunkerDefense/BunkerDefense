#pragma once
#include "ObjectManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Item.h"
#include "InputManager.h"
#include "Math.h"


class Player :
	public Object
{
	PLAYER_ANISTATE ani_state;				//�ִϸ��̼� ��¿� ����
	float m_greCoolTime;
	Object* m_pItem;						// ������
	map<int, Object*> m_itemBag;			// ������ ����

	PLAYER_STATE m_state;			    	// �÷��̾� ����
	ITEM_TAG item_state;			    	// ������ ���� ����
	GRENADE_STATE gre_state;				// ����ź ���� ����
										   
	Vector m_prevMousePos;				    // ���� ���콺 ��ǥ��
	float HitPoint;
	//float m_sight;						// �þ� ����

	//��ü ���� ��
	INT All_Bullet_Pistol;
	INT All_Bullet_Shot;
	INT All_Bullet_Laser;
	INT All_Bullet_Machine;

	//�������ִ� ��
	INT In_Bullet_Pistol;
	INT In_Bullet_Shot;
	INT In_Bullet_Laser;
	INT In_Bullet_Machine;


	INT Count_Grenade;
	INT Count_Radio;
	INT Count_Napalm;
	INT Count_Repair;

	INT InBulletCount;
	INT MaxBulletCount;
	INT AllBulletCount;
	int m_money;
	int m_score;

	float m_lagerChargerTime;				// �������� ���� �ð�
	UIProgressBar* m_lasergunCharger;		//�������� ���� ������ ����.
	bool m_laserGunShot;



public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	// �� �̹����� ���� �׷��ִ� ��ġ ���� ����
	Vector DrawPos();

//	void ThrowState(float deltaTime);
	void AttackState(float deltaTime);
	void ShopState();

	// �������� ���濡 �߰��ϴ� �Լ�
	void AddItem(Object* pItem); 

	// ��ȣ �Է½� �������� �����ϴ� �Լ�
	void SetItem();

	// �ѽ�� �ִϸ��̼� ������ ���� �������� Idle�ִϸ��̼����� �����ִ� �Լ�
	void SetIdleAnimation();

	// �� �� �� �ִϸ��̼� �������ִ� �Լ�
	void SetShotAnimation();

	// �� �� �� �Ҹ� ����ϴ� �Լ�
	void SetShotSound();

	// �������� ���� ���� ������Ʈ ���ִ� �Լ�
	void LaserChargerUpdate(float deltaTime);

	// ���� �������� ȣ��
	Object* GetCurrentItem() { return m_pItem; }

	ITEM_TAG GetItemState() { return item_state; }
	GRENADE_STATE GetGreState() { return gre_state; }

	// �÷��̾��� ���� �� �� ȣ��/�߰� �Լ�
	int GetScore() { return m_score; }
	void AddScore(int addScore) { m_score += addScore; }
	int GetMoney() { return m_money; }
	void AddMoney(int addMoney) { m_money += addMoney; }

	map<int, Object*> GetItemBag() { return m_itemBag; }

	//���� ź�� ����
	INT getBulletCount() { return InBulletCount; }
	INT getAllBullet() { return AllBulletCount; }
	INT getMaxBullet() { return MaxBulletCount; }
	void BulletUse(INT state);
	void BulletReload();
	void SaveBullet(INT item_tag);
	void CheckBullet();

	UIProgressBar* GetLaserChargerBar() { return m_lasergunCharger; }
};

