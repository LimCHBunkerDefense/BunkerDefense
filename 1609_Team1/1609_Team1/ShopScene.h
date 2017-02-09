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
	Sprite* m_pNpcIcon;
	Sprite* m_pTalkBox;

	BUTTON_TAG m_currentButton;				// 현재 버튼이 무엇인지 태그값으로 확인하는 변수
	Item* m_selectedButton;					// 선택된 버튼이 무엇인지를 나나태는 변수
	Item* m_currentItem;					// 현재 아이템이 무엇인지를 나타내는 변수

	// 상점에 있는 버튼이 클릭되었나를 확인하는 bool 변수
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

	void ItemListWnd();											// 아이템 리스트 창
	void ItemStatWnd();											// 아이템 정보 창

	Item* GetSelectedItem() { return m_selectedItem; }
	void SetSelectedItem(int itemID)
	{
		FOR_LIST(Item*, m_itemList)
		{
			if ((*it)->GetID() == itemID) 
			{ 
				m_selectedItem = (*it); 
				break;
			}
		}
	}

	void SetCurrentButton(BUTTON_TAG buttonTag) { m_currentButton = buttonTag; }

	// 버튼이 클릭되었나를 확인하는 bool변수의 GetSet함수
	bool GetIsWeaponClicked() { return IsWeaponClicked; }
	void SetIsWeaponClicked(bool ON) { IsWeaponClicked = ON; }
	bool GetIsBulletClicked() { return IsBulletClicked; }
	void SetIsBulletClicked(bool ON) { IsBulletClicked = ON; }
	bool GetIsUsingItemClicked() { return IsUsingItemClicked; }
	void SetIsUsingItemClicked(bool ON) { IsUsingItemClicked = ON; }
	bool GetIsBuyClicked() { return IsBuyClicked; }
	void SetIsBuyClicked(bool ON) { IsBuyClicked = ON; }
};