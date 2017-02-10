#include "ShopScene.h"

ShopScene::ShopScene()
{
	RENDER->LoadImageFile(TEXT("shopBG"), TEXT("Image/BackGround/shopBG.png"));
	RENDER->LoadImageFile(TEXT("shopNPC"), TEXT("Image/NPC/shopnpc.png"));
	RENDER->LoadImageFile(TEXT("talkBox"), TEXT("Image/NPC/talk_box.png"));
	RENDER->LoadImageFile(TEXT("MarketBG"), TEXT("Image/NPC/MarketBG.png"));
	RENDER->LoadImageFile(TEXT("Infobox_bg"), TEXT("Image/NPC/infobox_bg.png"));

	// itemDB 생성
	ITEM->Init();

	// ItemList에 Item Database 저장
	m_itemList.push_back(new Item(1001));
	m_itemList.push_back(new Item(1002));
	m_itemList.push_back(new Item(1003));
	m_itemList.push_back(new Item(1004));
	m_itemList.push_back(new Item(1005));
	m_itemList.push_back(new Item(1006));
	m_itemList.push_back(new Item(1007));
	m_itemList.push_back(new Item(1008));
	m_itemList.push_back(new Item(1009));
	m_itemList.push_back(new Item(1010));
	m_itemList.push_back(new Item(1011));
	m_itemList.push_back(new Item(1012));

	IsWeaponClicked = false;
	IsBulletClicked = false;
	IsUsingItemClicked = false;
}


ShopScene::~ShopScene()
{

}

void ShopScene::OnEnter()
{
	RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);

	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("shopBG")), 1.0f, 0, 0));
	NEW_OBJECT(m_pNpcIcon, Sprite(RENDER->GetImage(TEXT("shopNPC")), 1.3f, 0, 0));
	NEW_OBJECT(m_pTalkBox, Sprite(RENDER->GetImage(TEXT("talkBox")), 0.65, 0, 0));
	NEW_OBJECT(m_pMarketBG, Sprite(RENDER->GetImage(TEXT("MarketBG")), 0.815, 0, 0));
	NEW_OBJECT(m_pInfoBoxBG, Sprite(RENDER->GetImage(TEXT("Infobox_bg")), 0.81, 0, 0));

	CreateList();		// 리스트 생성
	ShowCursor(true);	// 마우스 커서 보이게
}

void ShopScene::OnUpdate(float deltaTime)
{
	OBJECT->Update(deltaTime);
}

void ShopScene::OnExit()
{
	m_boxList.clear();				// 박스 리스트 소멸
	m_selectedItem = NULL;			// 선택한 아이템 삭제
	m_currentButton = BUTTON_NONE;	// 현재 선택한 버튼값 삭제

	IsWeaponClicked = false;		// 클릭변수 삭제
	IsBulletClicked = false;
	IsUsingItemClicked = false;
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

	RENDER->DrawRect(Vector(630, 50), Vector (150, 50), ColorF::BlanchedAlmond);
	RENDER->DrawT(TEXT("SHOP"), 600, 35, ColorF::BlanchedAlmond, 25);
	RENDER->DrawRect(Vector(950, 450),Vector(320, 300),ColorF::AntiqueWhite, 3);
	RENDER->DrawT(TEXT("-아이템 정보-"), 880, 335, ColorF::BlanchedAlmond, 20);
	//pMainCamera->DrawT(TEXT("ATK:"), 800, 495, ColorF::AntiqueWhite, 15);
	if (m_selectedItem != NULL)
	{
		pMainCamera->DrawT(m_selectedItem->GetName(), 870, 395, ColorF::AntiqueWhite, 15);
		pMainCamera->DrawT(m_selectedItem->GetInfo(), 830, 420, ColorF::AntiqueWhite, 15);
		
		// float 값 사용해서 text 출력
		TCHAR number[50] = {};
		swprintf_s(number, TEXT("ATK: %.1f"), m_selectedItem->GetAttack());
		pMainCamera->DrawT(number, 850, 495, ColorF::AntiqueWhite, 15);
		swprintf_s(number, TEXT("DEF: %.1f"), m_selectedItem->GetDefense());
		pMainCamera->DrawT(number, 930, 495, ColorF::AntiqueWhite, 15);

		
	}

	//RENDER->DrawRect(Vector(135, 450), Vector(150, 150), ColorF::Aqua, 3);
	//RENDER->DrawCircle(Vector(135, 450), 50, ColorF::Aqua, 3);
	//RENDER->DrawT(TEXT(" NPC\nICON"), 110, 420, ColorF::Aqua, 20);

	//RENDER->DrawCircle(Vector(135, 250), 50, ColorF::Aqua, 3);
	//RENDER->DrawT(TEXT(" NPC\nTalk Box"), 110, 230, ColorF::Aqua, 16);

	ItemListWnd();
	ItemStatWnd();

}

void ShopScene::CreateList()
{
	// BoxList에 Box Database 저장
	AddBoxList(new Box(BUTTON_WEAPON, Vector(420, 235), Vector(120, 180)));
	AddBoxList(new Box(BUTTON_BULLET, Vector(550, 235), Vector(120, 180)));
	AddBoxList(new Box(BUTTON_USINGITEM, Vector(680, 235), Vector(120, 180)));

	AddBoxList(new Box(BUTTON_FIRST, Vector(550, 375), Vector(400, 60)));  // 소분류 아이템들 - index 3부터
	AddBoxList(new Box(BUTTON_SECOND, Vector(550, 435), Vector(400, 60)));
	AddBoxList(new Box(BUTTON_THIRD, Vector(550, 495), Vector(400, 60)));
	AddBoxList(new Box(BUTTON_FORTH, Vector(550, 555), Vector(400, 60)));

	AddBoxList(new Box(BUTTON_BUY, Vector(885, 700), Vector(125, 35)));	// 구매 버튼 박스
}

void ShopScene::ItemListWnd()
{
	//아이템 종류 목차
	//RENDER->DrawRect(Vector(550, 235), Vector(400, 220), ColorF::OrangeRed);
	RENDER->DrawRect(Vector(418, 232), Vector(120, 180), ColorF::Tomato);
	RENDER->DrawT(TEXT("    ITEM\nWEAPON"), 374, 215, ColorF::Tomato, 20);

	RENDER->DrawRect(Vector(550, 232), Vector(120, 180), ColorF::Khaki);
	RENDER->DrawT(TEXT("  ITEM\nBULLET"), 515, 215, ColorF::Khaki, 20);

	RENDER->DrawRect(Vector(680, 232), Vector(120, 180), ColorF::HotPink);
	RENDER->DrawT(TEXT("      ITEM\nUSINGITEM"), 625, 215, ColorF::HotPink, 20);

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

	list<Item*> itemList = SCENE->GetScene(SCENE_SHOP)->GetItemList();
	int weaponIndex = 0;
	int bulletIndex = -4;
	int usingItemIndex = -8;
	Item* pItem;

	switch (m_currentButton)
	{
	case BUTTON_WEAPON:
		FOR_LIST(Item*, itemList)
		{
			weaponIndex++;
			pItem = ((*it)->GetTag() == ITEM_WEAPON) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 385, 300 + weaponIndex * 60, ColorF::Tomato, 20.0f, ALIGN_CENTER);
			}
		}
		break;
	case BUTTON_BULLET:
		FOR_LIST(Item*, itemList)
		{
			bulletIndex++;
			pItem = ((*it)->GetTag() == ITEM_BULLET) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 385, 300 + bulletIndex * 60, ColorF::Khaki, 20.0f, ALIGN_CENTER);
			}
		}
		break;
	case BUTTON_USINGITEM:
		FOR_LIST(Item*, itemList)
		{ 
			usingItemIndex++;
			pItem = ((*it)->GetTag() == ITEM_USINGITEM) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 385, 300 + usingItemIndex * 60, ColorF::HotPink, 20.0f, ALIGN_CENTER);
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
	RENDER->DrawRect(Vector(950, 235), Vector(100, 100), ColorF::Aqua, 3);
	RENDER->DrawT(TEXT("ITEM\nICON"), 930, 215, ColorF::Aqua, 20);


	RENDER->DrawRect(Vector(940, 650), Vector(125, 35), ColorF::Aquamarine, 3);
	RENDER->DrawT(TEXT("수 량"), 920, 635, ColorF::Aquamarine, 20);

	RENDER->DrawT(TEXT("BUY"), 860, 688, ColorF::Aquamarine, 20);
	RENDER->DrawRect(Vector(1025, 700), Vector(125, 35), ColorF::Aquamarine, 3);
	RENDER->DrawT(TEXT("나가기 F3"), 985, 686, ColorF::Aquamarine, 20);
	//RENDER->DrawT(TEXT("ITEM INFO"), 750, 400, ColorF::Red, 25);
}