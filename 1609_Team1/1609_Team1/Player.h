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
	float m_greCoolTime;
	Object* m_pItem;						// ������
	map<int, Object*> m_itemBag;			// ������ ����

	PLAYER_STATE m_state;			    	// �÷��̾� ����
	ITEM_TAG item_state;			    	// ������ ���� ����
	GRENADE_STATE gre_state;				// ����ź ���� ����
										   
	Vector m_prevMousePos;				    // ���� ���콺 ��ǥ��
	float HitPoint;
	//float m_sight;						// �þ� ����

	int m_money;
	int m_score;


public:
	Player();
	Player(OBJ_TAG tag);
	~Player();
	
	void Update(float deltaTime);
	void Draw(Camera* pCamera);

//	void ThrowState(float deltaTime);
	void AttackState(float deltaTime);
	void ShopState();

	// �������� ���濡 �߰��ϴ� �Լ�
	void AddItem(Object* pItem); 

	// ��ȣ �Է½� �������� �����ϴ� �Լ�
	void SetItem();

	// ���� �������� ȣ��
	Object* GetCurrentItem() { return m_pItem; }

	ITEM_TAG GetItemState() { return item_state; }

	// �÷��̾��� ���� �� �� ȣ��/�߰� �Լ�
	int GetScore() { return m_score; }
	void AddScore(int addScore) { m_score += addScore; }
	int GetMoney() { return m_money; }
	void AddMoney(int addMoney) { m_money += addMoney; }
	map<int, Object*> GetItemBag() { return m_itemBag; }
};

