#pragma once
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Common.h"
#include "Item.h"

class ShopScene :
	public IScene
{
	//각 배경 및 박스 출력용 Sprite변수(각각 필요할듯하여 만들었는데 합치고 싶...습니다)
	Sprite* m_pBg;
	Sprite* m_pNpcIcon;
	Sprite* m_pTalkBox;
	Sprite* m_pMarketBG;
	Sprite* m_pInfoBoxBG;
	Sprite* m_pShopTitleBG;
	Sprite* m_pShopBT;
	Sprite* m_pSelectBT;
	Sprite* m_pClickBT;
	Sprite* m_pClickBT2;
	Sprite* m_pMenuBT;
	Sprite* m_pListBarBG;
	Sprite* m_pListBar;

	Sprite* m_pPistol;
	Sprite* m_pShotGun;
	Sprite* m_pMachineGun;
	Sprite* m_pLaserGun;
	Sprite* m_pPistolBullet;
	Sprite* m_pShotGunBullet;
	Sprite* m_pMachineGunBullet;
	Sprite* m_pLaserGunBullet;
	Sprite* m_pGrenade;
	Sprite* m_pAirBomb;
	Sprite* m_pFireCapsule;
	Sprite* m_pRepair;


	BUTTON_TAG m_currentButton;				// 현재 버튼이 무엇인지 태그값으로 확인하는 변수
	Item* m_selectedButton;					// 선택된 버튼이 무엇인지를 나나태는 변수
	Item* m_currentItem;					// 현재 아이템이 무엇인지를 나타내는 변수

	// 상점에 있는 버튼이 클릭되었나를 확인하는 bool 변수
	bool IsWeaponClicked;
	bool IsBulletClicked;
	bool IsUsingItemClicked;
	bool IsBuyClicked;

	// 상점에 있는 수량 관련 변수
	bool IsCountClicked;
	int m_inputCount;
	bool m_inputOnOff;

public:
	ShopScene();
	~ShopScene();

	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void CreateBoxList();										// 박스 리스트들을 생성하는 함수

	void ItemListWnd();											// 아이템 리스트 창
	void ItemStatWnd();											// 아이템 정보 창
	void ShowText();											// 아이템 정보 창에 정보를 보여주는 함수 (선택된 아이템마다 다른 정보를 뜨게함)
	Sprite* ShowIcon();											// 아이템 정보 창에서 아이템 아이콘을 보여주는 함수

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

	// 버튼이 클릭되었나를 확인하는 bool변수의 GetSet함수
	bool GetIsWeaponClicked() { return IsWeaponClicked; }
	void SetIsWeaponClicked(bool ON) { IsWeaponClicked = ON; }
	bool GetIsBulletClicked() { return IsBulletClicked; }
	void SetIsBulletClicked(bool ON) { IsBulletClicked = ON; }
	bool GetIsUsingItemClicked() { return IsUsingItemClicked; }
	void SetIsUsingItemClicked(bool ON) { IsUsingItemClicked = ON; }
	bool GetIsBuyClicked() { return IsBuyClicked; }
	void SetIsBuyClicked(bool ON) { IsBuyClicked = ON; }

	// 상점에 있는 수량 관련 GetSet함수
	bool GetIsCountClicked() { return IsCountClicked; }
	void SetIsCountClicked(bool ON) { IsCountClicked = ON; }
	int GetInputCount() { return m_inputCount; }
	void SetInputCount(int addCount);
	void InputCountClear();
	bool GetInputOnOff() { return m_inputOnOff; }
	void SetInputOnOff(bool ON) { m_inputOnOff = ON; }
	
};