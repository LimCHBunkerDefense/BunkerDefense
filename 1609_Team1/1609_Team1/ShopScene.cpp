#include "ShopScene.h"

ShopScene::ShopScene()
{
	RENDER->LoadImageFile(TEXT("shopBG"), TEXT("Image/BackGround/shopBG.png"));
	RENDER->LoadImageFile(TEXT("shopNPC"), TEXT("Image/NPC/shopnpc.png"));
	RENDER->LoadImageFile(TEXT("talkBox"), TEXT("Image/NPC/talk_box.png"));
	RENDER->LoadImageFile(TEXT("MarketBG"), TEXT("Image/NPC/MarketBG.png"));
	RENDER->LoadImageFile(TEXT("Infobox_bg"), TEXT("Image/NPC/infobox_bg.png"));
	RENDER->LoadImageFile(TEXT("ShopTitle"), TEXT("Image/NPC/ShopTitle.png"));
	RENDER->LoadImageFile(TEXT("ShopBT"), TEXT("Image/NPC/shopbt.png"));
	RENDER->LoadImageFile(TEXT("SelectBT"), TEXT("Image/NPC/shopselectbt.png"));
	RENDER->LoadImageFile(TEXT("MenuBT"), TEXT("Image/NPC/ItemMENU.png"));
	RENDER->LoadImageFile(TEXT("ClickBT"), TEXT("Image/NPC/shopbt2.png"));
	RENDER->LoadImageFile(TEXT("ClickedBT"), TEXT("Image/NPC/shopselectbt2.png"));

	RENDER->LoadImageFile(TEXT("PistolIcon"), TEXT("Image/Item/Shop_Icon/Pistol.png"));
	RENDER->LoadImageFile(TEXT("ShotGunIcon"), TEXT("Image/Item/Shop_Icon/ShotGun.png"));
	RENDER->LoadImageFile(TEXT("MachineGunIcon"), TEXT("Image/Item/Shop_Icon/MachineGun.png"));
	RENDER->LoadImageFile(TEXT("LaserGunIcon"), TEXT("Image/Item/Shop_Icon/LaserGun.png"));
	RENDER->LoadImageFile(TEXT("PSBulletIcon"), TEXT("Image/Item/Shop_Icon/PistolBullet.png"));
	RENDER->LoadImageFile(TEXT("SGBulletIcon"), TEXT("Image/Item/Shop_Icon/ShotGunBullet.png"));
	RENDER->LoadImageFile(TEXT("MGBulletIcon"), TEXT("Image/Item/Shop_Icon/MachineGunBullet.png"));
	RENDER->LoadImageFile(TEXT("LGBulletIcon"), TEXT("Image/Item/Shop_Icon/LaserGunBullet.png"));
	RENDER->LoadImageFile(TEXT("GrenadeIcon"), TEXT("Image/Item/Shop_Icon/Grenade.png"));
	RENDER->LoadImageFile(TEXT("AirBombIcon"), TEXT("Image/Item/Shop_Icon/AirBomb.png"));
	RENDER->LoadImageFile(TEXT("FireCapsuleIcon"), TEXT("Image/Item/Shop_Icon/FireCapsule.png"));
	RENDER->LoadImageFile(TEXT("RepairIcon"), TEXT("Image/Item/Shop_Icon/Repair.png"));

	m_pPistol = NEW_OBJECT(m_pPistol, Sprite(RENDER->GetImage(TEXT("PistolIcon"))));
	m_pShotGun = NEW_OBJECT(m_pShotGun, Sprite(RENDER->GetImage(TEXT("ShotGunIcon"))));
	m_pMachineGun = NEW_OBJECT(m_pMachineGun, Sprite(RENDER->GetImage(TEXT("MachineGunIcon"))));
	m_pLaserGun = NEW_OBJECT(m_pLaserGun, Sprite(RENDER->GetImage(TEXT("LaserGunIcon"))));
	m_pPistolBullet = NEW_OBJECT(m_pPistolBullet, Sprite(RENDER->GetImage(TEXT("PSBulletIcon"))));
	m_pShotGunBullet = NEW_OBJECT(m_pShotGunBullet, Sprite(RENDER->GetImage(TEXT("SGBulletIcon"))));
	m_pMachineGunBullet = NEW_OBJECT(m_pMachineGunBullet, Sprite(RENDER->GetImage(TEXT("MGBulletIcon"))));
	m_pLaserGunBullet = NEW_OBJECT(m_pLaserGunBullet, Sprite(RENDER->GetImage(TEXT("LGBulletIcon"))));
	m_pGrenade = NEW_OBJECT(m_pGrenade, Sprite(RENDER->GetImage(TEXT("GrenadeIcon"))));
	m_pAirBomb = NEW_OBJECT(m_pAirBomb, Sprite(RENDER->GetImage(TEXT("AirBombIcon"))));
	m_pFireCapsule = NEW_OBJECT(m_pFireCapsule, Sprite(RENDER->GetImage(TEXT("FireCapsuleIcon"))));
	m_pRepair = NEW_OBJECT(m_pRepair, Sprite(RENDER->GetImage(TEXT("RepairIcon"))));

	IsWeaponClicked = false;
	IsBulletClicked = false;
	IsUsingItemClicked = false;
	IsCountClicked = false;
}


ShopScene::~ShopScene()
{

}

void ShopScene::OnEnter()
{
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("shopBG")), 1.0f, 0, 0));
	NEW_OBJECT(m_pNpcIcon, Sprite(RENDER->GetImage(TEXT("shopNPC")), 1.3f, 0, 0));
	NEW_OBJECT(m_pTalkBox, Sprite(RENDER->GetImage(TEXT("talkBox")), 0.65, 0, 0));
	NEW_OBJECT(m_pMarketBG, Sprite(RENDER->GetImage(TEXT("MarketBG")), 0.815, 0, 0));
	NEW_OBJECT(m_pInfoBoxBG, Sprite(RENDER->GetImage(TEXT("Infobox_bg")), 0.81, 0, 0));
	NEW_OBJECT(m_pShopTitleBG, Sprite(RENDER->GetImage(TEXT("ShopTitle")), 0.85f, 0, 0));
	NEW_OBJECT(m_pShopBT, Sprite(RENDER->GetImage(TEXT("ShopBT")), 0.85f, 0, 0));
	NEW_OBJECT(m_pSelectBT, Sprite(RENDER->GetImage(TEXT("SelectBT")), 0.85f, 0, 0));
	NEW_OBJECT(m_pMenuBT, Sprite(RENDER->GetImage(TEXT("MenuBT")), 0.95f, 0, 0));
	NEW_OBJECT(m_pClickBT, Sprite(RENDER->GetImage(TEXT("ClickBT")), 0.85f, 0, 0));
	NEW_OBJECT(m_pClickBT2, Sprite(RENDER->GetImage(TEXT("ClickedBT")), 0.85f, 0, 0));

	CreateBoxList();		// 리스트 생성
	ShowCursor(true);		// 마우스 커서 보이게

	m_inputCount = 0;
	m_inputOnOff = false;
}

void ShopScene::OnUpdate(float deltaTime)
{
	OBJECT->Update(deltaTime);
	RENDER->GetCamera(CAM_MAIN)->SetCenterPos(Vector(0,0));
}

void ShopScene::OnExit()
{
	m_boxList.clear();				// 박스 리스트 소멸
	m_selectedItem = NULL;			// 선택한 아이템 삭제
	m_currentButton = BUTTON_NONE;	// 현재 선택한 버튼값 삭제

	IsWeaponClicked = false;		// 클릭변수 삭제
	IsBulletClicked = false;
	IsUsingItemClicked = false;
	IsCountClicked = false;
}

void ShopScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMainCamera->Draw(m_pBg, Vector(0, 0));
	pMainCamera->Draw(m_pMarketBG, Vector(350, 124));
	pMainCamera->Draw(m_pInfoBoxBG, Vector(788, 300));
	pMainCamera->Draw(m_pTalkBox, Vector(20, 115)); // talkbox image
	pMainCamera->DrawT(TEXT("***님 반갑습니다. \n ***상점에 오신걸 환영합니다."), 84, 190, ColorF::BlanchedAlmond, 15);
	pMainCamera->Draw(m_pNpcIcon, Vector(-138, 220)); // npc image

	//샾 UI
	//RENDER->DrawRect(Vector(630, 50), Vector (150, 50), ColorF::BlanchedAlmond);
	//RENDER->DrawT(TEXT("SHOP"), 600, 35, ColorF::BlanchedAlmond, 25);
	pMainCamera->Draw(m_pShopTitleBG, Vector(VIEW_WIDTH * 0.45f, 20));

	//아이템 매뉴
	pMainCamera->Draw(m_pMenuBT, Vector(366, 160));
	pMainCamera->Draw(m_pMenuBT, Vector(496, 160));
	pMainCamera->Draw(m_pMenuBT, Vector(624, 160));


	//버튼 이미지(테스트)

	pMainCamera->Draw(m_pShopBT, Vector(820, 680)); // 일반 버튼1
	pMainCamera->Draw(m_pClickBT, Vector(820, 730)); // 선택 버튼1

	pMainCamera->Draw(m_pSelectBT, Vector(960, 680)); //일반 버튼2
	pMainCamera->Draw(m_pClickBT2, Vector(960, 730)); //선택 버튼2
	if (IsBuyClicked == true)

	//RENDER->DrawRect(Vector(950, 450),Vector(320, 300),ColorF::AntiqueWhite, 3);
	RENDER->DrawT(TEXT("-아이템 정보-"), 880, 335, ColorF::BlanchedAlmond, 20);
	//pMainCamera->DrawT(TEXT("ATK:"), 800, 495, ColorF::AntiqueWhite, 15);

	ShowText();

	//RENDER->DrawRect(Vector(135, 450), Vector(150, 150), ColorF::Aqua, 3);
	//RENDER->DrawCircle(Vector(135, 450), 50, ColorF::Aqua, 3);
	//RENDER->DrawT(TEXT(" NPC\nICON"), 110, 420, ColorF::Aqua, 20);

	//RENDER->DrawCircle(Vector(135, 250), 50, ColorF::Aqua, 3);
	//RENDER->DrawT(TEXT(" NPC\nTalk Box"), 110, 230, ColorF::Aqua, 16);

	ItemListWnd();
	ItemStatWnd();

	pMainCamera->Draw(ShowIcon(), Vector(900, 220));
}

void ShopScene::CreateBoxList()
{
	// BoxList에 Box Database 저장
	AddBoxList(new Box(BUTTON_WEAPON, Vector(425, 235), Vector(120, 150)));	// 중분류 아이템들
	AddBoxList(new Box(BUTTON_BULLET, Vector(555, 235), Vector(120, 150)));
	AddBoxList(new Box(BUTTON_USINGITEM, Vector(685, 235), Vector(120, 150)));

	AddBoxList(new Box(BUTTON_FIRST, Vector(560, 375), Vector(380, 60)));	// 소분류 아이템들 - index 3부터
	AddBoxList(new Box(BUTTON_SECOND, Vector(560, 435), Vector(380, 60)));
	AddBoxList(new Box(BUTTON_THIRD, Vector(560, 495), Vector(380, 60)));
	AddBoxList(new Box(BUTTON_FORTH, Vector(560, 555), Vector(380, 60)));

	AddBoxList(new Box(BUTTON_COUNT, Vector(945, 650), Vector(125, 35)));	// 수량 버튼 박스
	AddBoxList(new Box(BUTTON_BUY, Vector(888, 704), Vector(128, 45)));		// 구매 버튼 박스
	AddBoxList(new Box(BUTTON_EXIT, Vector(1028, 704), Vector(128, 45)));	// 종료 버튼 박스
}

void ShopScene::ItemListWnd()
{
	//아이템 종류 목차
	//RENDER->DrawRect(Vector(550, 235), Vector(400, 220), ColorF::OrangeRed);
	//RENDER->DrawRect(Vector(425, 234), Vector(120, 150), ColorF::Tomato);
	RENDER->DrawT(TEXT("    ITEM\nWEAPON"), 380, 215, ColorF::AntiqueWhite, 18);

	//RENDER->DrawRect(Vector(556, 234), Vector(120, 150), ColorF::Khaki);
	RENDER->DrawT(TEXT("  ITEM\nBULLET"), 520, 215, ColorF::AntiqueWhite, 18);

	//RENDER->DrawRect(Vector(685, 234), Vector(120, 150), ColorF::HotPink);
	RENDER->DrawT(TEXT("      ITEM\nUSINGITEM"), 632, 215, ColorF::AntiqueWhite, 18);


	//RENDER->DrawRect(Vector(550, 560),Vector(400, 430),ColorF::Red);
	//RENDER->DrawLine(Vector(350, 408), Vector(750, 408), ColorF::Red);
	//RENDER->DrawLine(Vector(350, 462), Vector(750, 462), ColorF::Red);
	//RENDER->DrawLine(Vector(350, 524), Vector(750, 524), ColorF::Red);
	//RENDER->DrawLine(Vector(350, 584), Vector(750, 584), ColorF::Red);
	//RENDER->DrawLine(Vector(300, 644), Vector(700, 644), ColorF::Red);
	//RENDER->DrawLine(Vector(300, 704),Vector(700, 704),ColorF::Red);

	if (SCENE->GetColliderOnOff())
	{
		list<Box*> boxList = GetBoxList();
		FOR_LIST(Box*, boxList)
		{
			RENDER->DrawRect((*it)->LeftTop() + (*it)->size * 0.5f, (*it)->size, ColorF::Yellow, 3.0f);
		}
	}

	list<Object*> itemList = OBJECT->GetShopItemList();
	int weaponIndex = 0;
	int bulletIndex = -4;
	int usingItemIndex = -8;
	Object* pItem;

	switch (m_currentButton)
	{
	case BUTTON_WEAPON:
		FOR_LIST(Object*, itemList)
		{
			weaponIndex++;
			pItem = ((*it)->GetItemTypeTag() == ITEMTYPE_WEAPON) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 385, 300 + weaponIndex * 60, ColorF::AntiqueWhite, 20.0f, ALIGN_CENTER);
			}
		}
		break;
	case BUTTON_BULLET:
		FOR_LIST(Object*, itemList)
		{
			bulletIndex++;
			pItem = ((*it)->GetItemTypeTag() == ITEMTYPE_BULLET) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 385, 300 + bulletIndex * 60, ColorF::AntiqueWhite, 20.0f, ALIGN_CENTER);
			}
		}
		break;
	case BUTTON_USINGITEM:
		FOR_LIST(Object*, itemList)
		{ 
			usingItemIndex++;
			pItem = ((*it)->GetItemTypeTag() == ITEMTYPE_USINGITEM) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 385, 300 + usingItemIndex * 60, ColorF::AntiqueWhite, 20.0f, ALIGN_CENTER);
			}
		}
		break;
	}
	//RENDER->DrawT(TEXT("ITEM LIST"), 430, 550, ColorF::Red, 25);
}
void ShopScene::ItemStatWnd()
{
	//선택 아이탬 정보
	//RENDER->DrawRect(Vector(950, 450), Vector(400, 650), ColorF::Yellow);
	//RENDER->DrawRect(Vector(950, 235), Vector(100, 100), ColorF::Aqua, 3);
	//RENDER->DrawT(TEXT("ITEM\nICON"), 930, 215, ColorF::Aqua, 20);


	RENDER->DrawRect(Vector(945, 650), Vector(125, 35), ColorF::Aquamarine, 3);
	if (m_inputOnOff == false)
	{
		RENDER->DrawT(TEXT("수 량"), 920, 635, ColorF::White, 20);
	}
	else if (m_inputOnOff == true)
	{
		TCHAR text[50] = {};
		wsprintf(text, TEXT("%d"), m_inputCount);
		RENDER->DrawT(text, 920, 635, ColorF::White, 20);
	}

	//RENDER->DrawT(TEXT("BUY"), 860, 688, ColorF::Aquamarine, 20);
	//RENDER->DrawT(TEXT("나가기"), 985, 686, ColorF::Aquamarine, 20);

	//RENDER->DrawT(TEXT("ITEM INFO"), 750, 400, ColorF::Red, 25);
}

void ShopScene::SetInputCount(int addCount)
{
	if (m_inputCount == 0) m_inputCount += addCount;
	else if (m_inputCount != 0) m_inputCount = m_inputCount * 10 + addCount;

	map<int,Object*> playerBag = OBJECT->GetPlayer()->GetItemBag();
	Object* pItem = NULL;
	if (playerBag.find(m_selectedItem->GetTag()) != playerBag.end())
	{
		pItem = playerBag[m_selectedItem->GetTag()];
	}

	int maxCount = m_selectedItem->GetMaxCount();	// 아이템들이 구매할 수 있는 최대 갯수
	int buyCount = (pItem != NULL) ? maxCount - pItem->GetCurrentCount() : maxCount;																// 구매할 수 있는 수량


	switch (m_selectedItem->GetItemTypeTag())
	{
	case ITEMTYPE_WEAPON:
		if (pItem == NULL) m_inputCount = MATH->Clamp(m_inputCount, 0, buyCount);
		if (pItem != NULL) m_inputCount = 0;
		break;

	case ITEMTYPE_BULLET:
		if (pItem == NULL)
		{
			m_inputCount = MATH->Clamp(m_inputCount, 0, buyCount);
		}

		if (pItem != NULL)
		{
			if (pItem->GetTag() == ITEM_PSBULLET)
			{
				if (playerBag.find(ITEM_PISTOL) != playerBag.end())
				{
					m_inputCount = MATH->Clamp(m_inputCount, 0, buyCount);
				}
			}	
			if (pItem->GetTag() == ITEM_SGBULLET)
			{
				if (playerBag.find(ITEM_SGBULLET) != playerBag.end())
				{
					m_inputCount = MATH->Clamp(m_inputCount, 0, buyCount);
				}
			}
			if (pItem->GetTag() == ITEM_MGBULLET)
			{
				if (playerBag.find(ITEM_MACHINEGUN) != playerBag.end())
				{
					m_inputCount = MATH->Clamp(m_inputCount, 0, buyCount);
				}
			}

			if (pItem->GetTag() == ITEM_LGBULLET)
			{
				if (playerBag.find(ITEM_LASERGUN) != playerBag.end())
				{
					m_inputCount = MATH->Clamp(m_inputCount, 0, buyCount);
				}
			}
		}
		break;

	case ITEMTYPE_USINGITEM:
		m_inputCount = MATH->Clamp(m_inputCount, 0, buyCount);
		break;
	}	
}

void ShopScene::ShowText()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);

	if (m_selectedItem != NULL)
	{
		pMainCamera->DrawT(m_selectedItem->GetName(), 870, 330, ColorF::AntiqueWhite, 15);
		pMainCamera->DrawT(m_selectedItem->GetInfo(), 810, 365, ColorF::AntiqueWhite, 15);
		TCHAR number[50] = {};

		switch (m_selectedItem->GetItemTypeTag())
		{
		case ITEMTYPE_WEAPON:
			// 공격력
			swprintf_s(number, TEXT("ATK: %.1f"), m_selectedItem->GetAttack());
			pMainCamera->DrawT(number, 820, 440, ColorF::AntiqueWhite, 15);

			// 사정거리
			pMainCamera->DrawT(m_selectedItem->GetRangeStr(), 950, 440, ColorF::AntiqueWhite, 15);

			// 구매비용
			wsprintf(number, TEXT("Money : %d"), m_selectedItem->GetMoney());
			pMainCamera->DrawT(number, 820, 465, ColorF::AntiqueWhite, 15);
			break;

		case ITEMTYPE_BULLET:
			// 구매비용
			wsprintf(number, TEXT("Money : %d"), m_selectedItem->GetMoney());
			pMainCamera->DrawT(number, 820, 440, ColorF::AntiqueWhite, 15);
			break;

		case ITEMTYPE_USINGITEM:
			if (m_selectedItem->GetTag() != ITEM_BUNKERREPAIR)
			{
				// 공격력
				swprintf_s(number, TEXT("ATK: %.1f"), m_selectedItem->GetAttack());
				pMainCamera->DrawT(number, 820, 440, ColorF::AntiqueWhite, 15);

				// 사정거리
				pMainCamera->DrawT(m_selectedItem->GetRangeStr(), 950, 440, ColorF::AntiqueWhite, 15);

				// 구매비용
				wsprintf(number, TEXT("Money : %d"), m_selectedItem->GetMoney());
				pMainCamera->DrawT(number, 820, 465, ColorF::AntiqueWhite, 15);
				break;
			}
			else
			{
				// 수리량
				swprintf_s(number, TEXT("Repair: %.1f"), m_selectedItem->GetRepair());
				pMainCamera->DrawT(number, 820, 440, ColorF::AntiqueWhite, 15);
			}
			break;

		}
	}
}

Sprite* ShopScene::ShowIcon()
{
	Sprite* pSprite;

	switch (m_selectedItem->GetTag())
	{
	case ITEM_PISTOL:
		pSprite = m_pPistol;
		break;

	case ITEM_SHOTGUN:
		pSprite = m_pShotGun;
		break;

	case ITEM_MACHINEGUN:
		pSprite = m_pMachineGun;
		break;

	case ITEM_LASERGUN:
		pSprite = m_pLaserGun;
		break;

	case ITEM_PSBULLET:
		pSprite = m_pPistolBullet;
		break;

	case ITEM_SGBULLET:
		pSprite = m_pShotGunBullet;
		break;

	case ITEM_MGBULLET:
		pSprite = m_pMachineGunBullet;
		break;

	case ITEM_LGBULLET:
		pSprite = m_pLaserGunBullet;
		break;

	case ITEM_GRENADE:
		pSprite = m_pGrenade;
		break;

	case ITEM_AIRBOMB:
		pSprite = m_pAirBomb;
		break;

	case ITEM_FIRECAPSULE:
		pSprite = m_pFireCapsule;
		break;

	case ITEM_BUNKERREPAIR:
		pSprite = m_pRepair;
		break;
	}

	return pSprite;
}