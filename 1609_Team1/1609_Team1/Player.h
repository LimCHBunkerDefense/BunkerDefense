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
	Object* m_pItem;						// ������
	map<int, Object*> m_itemBag;			// ������ ����

	PLAYER_STATE m_state;			    	// �÷��̾� ����
	ITEM_TAG item_state;			    	// ������ ���� ����
										   
	Vector m_prevMousePos;				    // ���� ���콺 ��ǥ��

	float HitPoint;
	//float m_sight;						// �þ� ����

public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void AttackState(float deltaTime);
	void ShopState();

	// �������� ���濡 �߰��ϴ� �Լ�
	void AddItem(Object* pItem); 

	// ��ȣ �Է½� �������� �����ϴ� �Լ�
	void SetItem();

	ITEM_TAG GetItemState() { return item_state; }
	map<int, Object*> GetItemBag() { return m_itemBag; }
};

