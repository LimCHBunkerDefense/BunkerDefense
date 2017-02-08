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
	BUTTON_TAG m_currentButton;				// ���� ��ư�� �������� �±װ����� Ȯ���ϴ� ����
	Item* m_selectedButton;					// ���õ� ��ư�� ���������� �����´� ����
	Item* m_currentItem;					// ���� �������� ���������� ��Ÿ���� ����

	// ������ �ߺз� ��ư�� Ŭ���Ǿ����� Ȯ���ϴ� bool ����
	bool IsWeaponClicked;
	bool IsBulletClicked;
	bool IsUsingItemClicked;

public:
	ShopScene();
	~ShopScene();
	
	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void ItemListWnd();											// ������ ����Ʈ â
	void ItemStatWnd();											// ������ ���� â


	Item* GetSelectedItem() { return m_selectedItem; }
	void SetSelectedItem(int itemID)
	{
		FOR_LIST(Item*, m_itemList)
		{
			if ((*it)->GetID() == itemID) m_selectedItem = (*it);
			break;
		}
	}
	// Item* SetSelectedItem(int m_itemID) 
	// { 
	// 	return m_selectedItem = ITEM->GetData(m_itemID); 
	// }

	void SetCurrentButton(BUTTON_TAG buttonTag) { m_currentButton = buttonTag; }

	bool GetIsWeaponClicked() { return IsWeaponClicked; }
	void SetIsWeaponClicked(bool ON) { IsWeaponClicked = ON; }
	bool GetIsBulletClicked() { IsBulletClicked; }
	void SetIsBulletClicked(bool ON) { IsBulletClicked = ON; }
	bool GetIsUsingItemClicked() { IsUsingItemClicked; }
	void SetIsUsingItemClicked(bool ON) { IsUsingItemClicked = ON; }
};