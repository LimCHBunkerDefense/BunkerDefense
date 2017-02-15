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
	RENDER->LoadImageFile(TEXT("ClickBT"), TEXT("Image/NPC/shopclicktbt.png"));

	IsWeaponClicked = false;
	IsBulletClicked = false;
	IsUsingItemClicked = false;
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
	NEW_OBJECT(m_pClickBT, Sprite(RENDER->GetImage(TEXT("ClickBT")), 0.85f, 0, 0));

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
	pMainCamera->Draw(m_pShopTitleBG, Vector(VIEW_WIDTH * 0.5f, 20));

	//버튼 이미지(테스트)
	pMainCamera->Draw(m_pSelectBT, Vector(960, 680)); //선택 버튼
	pMainCamera->Draw(m_pClickBT, Vector(900, 750)); // 클릭버튼
	pMainCamera->Draw(m_pShopBT, Vector(820, 680)); // 일반 버튼

	//RENDER->DrawRect(Vector(950, 450),Vector(320, 300),ColorF::AntiqueWhite, 3);
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

void ShopScene::CreateBoxList()
{
	// BoxList에 Box Database 저장
	AddBoxList(new Box(BUTTON_WEAPON, Vector(420, 235), Vector(120, 180)));	// 중분류 아이템들
	AddBoxList(new Box(BUTTON_BULLET, Vector(550, 235), Vector(120, 180)));
	AddBoxList(new Box(BUTTON_USINGITEM, Vector(680, 235), Vector(120, 180)));

	AddBoxList(new Box(BUTTON_FIRST, Vector(550, 375), Vector(400, 60)));	// 소분류 아이템들 - index 3부터
	AddBoxList(new Box(BUTTON_SECOND, Vector(550, 435), Vector(400, 60)));
	AddBoxList(new Box(BUTTON_THIRD, Vector(550, 495), Vector(400, 60)));
	AddBoxList(new Box(BUTTON_FORTH, Vector(550, 555), Vector(400, 60)));

	AddBoxList(new Box(BUTTON_COUNT, Vector(940, 650), Vector(125, 35)));	// 수량 버튼 박스
	AddBoxList(new Box(BUTTON_BUY, Vector(885, 700), Vector(125, 35)));		// 구매 버튼 박스
	AddBoxList(new Box(BUTTON_EXIT, Vector(1025, 700), Vector(125, 35)));	// 종료 버튼 박스
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
				RENDER->DrawT(pItem->GetName(), 385, 300 + weaponIndex * 60, ColorF::Tomato, 20.0f, ALIGN_CENTER);
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
				RENDER->DrawT(pItem->GetName(), 385, 300 + bulletIndex * 60, ColorF::Khaki, 20.0f, ALIGN_CENTER);
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
	if (m_inputCount != 0)
	{
		m_inputCount = MATH->Clamp(m_inputCount * 10 + addCount, 0, 1000);
	}
}