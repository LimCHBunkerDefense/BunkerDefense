#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Common.h"
#include "Item.h"

class ShopScene :
	public IScene
{
	Sprite* m_pBg;
	Box m_bBuyButton;

	Box m_bWeapon;
	Box m_bBullet;
	Box m_bItem;

	Box m_bMachineGun;				// �ӽŰ�
	Box m_bFireThrower;				// ȭ������

	Box m_bPistolBullet;			// ���� ź��
	Box m_bMachineGunBullet;		// �ӽŰ� ź��
	Box m_bFireThrowerBullet;		// ȭ������ ź��

	Box m_bGrenade;					// ����ź
	Box m_bAirBomb;					// ���� ����
	Box m_bRavaRegion;				// ȭ�� ����
	Box m_bBunckerRepair;			// ��Ŀ ����

	Item* m_selectedItem;
public:
	ShopScene();
	~ShopScene();
	
	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void ItemListWnd(); // ������ ����Ʈ â
	void ItemStatWnd(); // ������ ���� â

	Box GetButton() { return m_bBuyButton; }
	Item* GetSelectedItem() { return m_selectedItem; }
};

