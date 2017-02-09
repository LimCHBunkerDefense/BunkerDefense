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
	Item* m_pItem;								// ������
	list<Item*> m_itemBag;						// ������ ����

	PLAYER_STATE m_state;

	Vector m_vAngle;//�÷��̾� ���� ����

	Vector m_prevMousePos;//���� ���콺 ��ǥ��
	float m_sight;//�þ� ����



public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void AttackState(float deltaTime);
	void ShopState();

	void AddItem(Item* pItem) { m_itemBag.push_back(new Item(pItem->GetID())); }
};

