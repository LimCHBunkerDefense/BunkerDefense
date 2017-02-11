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
	//�� ��� �� �ڽ� ��¿� Sprite����(���� �ʿ��ҵ��Ͽ� ������µ� ��ġ�� ��...���ϴ�)
	Sprite* m_pBg;
	Sprite* m_pNpcIcon;
	Sprite* m_pTalkBox;
	Sprite* m_pMarketBG;
	Sprite* m_pInfoBoxBG;

	BUTTON_TAG m_currentButton;				// ���� ��ư�� �������� �±װ����� Ȯ���ϴ� ����
	Item* m_selectedButton;					// ���õ� ��ư�� ���������� �����´� ����
	Item* m_currentItem;					// ���� �������� ���������� ��Ÿ���� ����

	// ������ �ִ� ��ư�� Ŭ���Ǿ����� Ȯ���ϴ� bool ����
	bool IsWeaponClicked;
	bool IsBulletClicked;
	bool IsUsingItemClicked;
	bool IsBuyClicked;

public:
	ShopScene();
	~ShopScene();

	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void CreateBoxList();										// �ڽ� ����Ʈ���� �����ϴ� �Լ�

	void ItemListWnd();											// ������ ����Ʈ â
	void ItemStatWnd();											// ������ ���� â

	Object* GetSelectedItem() { return m_selectedItem; }
	void SetSelectedItem(int itemID)
	{
		list<Object*> pList = OBJECT->GetShopItemList();
		FOR_LIST(Object*, pList)
		{
			if ((*it)->GetID() == itemID) 
			{ 
				m_selectedItem = (*it); 
				break;
			}
		}
	}

	void SetCurrentButton(BUTTON_TAG buttonTag) { m_currentButton = buttonTag; }
	int GetCurrentButton() { return m_currentButton; }

	// ��ư�� Ŭ���Ǿ����� Ȯ���ϴ� bool������ GetSet�Լ�
	bool GetIsWeaponClicked() { return IsWeaponClicked; }
	void SetIsWeaponClicked(bool ON) { IsWeaponClicked = ON; }
	bool GetIsBulletClicked() { return IsBulletClicked; }
	void SetIsBulletClicked(bool ON) { IsBulletClicked = ON; }
	bool GetIsUsingItemClicked() { return IsUsingItemClicked; }
	void SetIsUsingItemClicked(bool ON) { IsUsingItemClicked = ON; }
	bool GetIsBuyClicked() { return IsBuyClicked; }
	void SetIsBuyClicked(bool ON) { IsBuyClicked = ON; }
};