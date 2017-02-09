#pragma once
#include "ObjectManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Item.h"
#include "InputManager.h"
#include "Math.h"


class Player :
	public Object
{
	Item* m_pItem;						// ������
	map<int, Item*> m_itemBag;			// ������ ����

	PLAYER_STATE m_state;				// �÷��̾� ����
	GUN_STATE m_gunState;				// �÷��̾ ��� �ִ� ���� ����

	Vector m_vAngle;					// �÷��̾� ���� ����
										   
	Vector m_prevMousePos;				// ���� ���콺 ��ǥ��
	float m_sight;						// �þ� ����



public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void AttackState(float deltaTime);
	void ShopState();

	// �������� ���濡 �߰��ϴ� �Լ�
	void AddItem(Item* pItem) { m_itemBag[pItem->GetID()] = new Item(pItem->GetID()); }

	// ��ȣ �Է½� �������� �����ϴ� �Լ�
	void SetItem();
};

