#include "ShopScene.h"

ShopScene::ShopScene()
{
	RENDER->LoadImageFile(TEXT("shopBG"), TEXT("Image/BackGround/shopBG.png"));
	//m_itemList.push_back();

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

	// BoxList에 Box Database 저장
	AddBoxList(new Box(ITEM_WEAPON, Vector(370, 235), Vector(120, 180)));
	AddBoxList(new Box(ITEM_BULLET, Vector(500, 235), Vector(120, 180)));
	AddBoxList(new Box(ITEM_USINGITEM, Vector(630, 235), Vector(120, 180)));

	AddBoxList(new Box(1, Vector(500, 375), Vector(400, 60)));  // 소분류 아이템들 - index 3부터
	AddBoxList(new Box(2, Vector(500, 435), Vector(400, 60)));
	AddBoxList(new Box(3, Vector(500, 495), Vector(400, 60)));
	AddBoxList(new Box(4, Vector(500, 555), Vector(400, 60)));

	AddBoxList(new Box(5, Vector(835, 700), Vector(125, 35)));	// 구매 버튼 박스

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

	// m_bBuyButton = Box(Vector(1000, 500), Vector(100, 50));
	// m_bWeapon = Box(Vector(480, 200), Vector(200, 50));
	// m_bBullet = Box(Vector(480, 280), Vector(200, 50));
	// m_bUsingItem = Box(Vector(480, 360), Vector(200, 50));
}

void ShopScene::OnUpdate(float deltaTime)
{
	OBJECT->Update(deltaTime);
}

void ShopScene::OnExit()
{

}

void ShopScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMainCamera->Draw(m_pBg, Vector(0, 0));


	RENDER->DrawRect(Vector(620, 50), Vector(150, 50), ColorF::BlanchedAlmond);
	RENDER->DrawT(TEXT("SHOP"), 590, 35, ColorF::BlanchedAlmond, 25);
	RENDER->DrawRect(Vector(900, 450),Vector(320, 300),ColorF::AntiqueWhite, 3);
	RENDER->DrawT(TEXT("-아이템 정보-"), 840, 335, ColorF::BlanchedAlmond, 20);

	if (m_selectedItem != NULL)
	{
		pMainCamera->DrawT(m_selectedItem->GetName(), 820, 395, ColorF::AntiqueWhite, 15);
		
		pMainCamera->DrawT(m_selectedItem->GetInfo(), 820, 490, ColorF::AntiqueWhite, 15);
	}

	RENDER->DrawRect(Vector(135, 450), Vector(150, 150), ColorF::Aqua, 3);
	RENDER->DrawCircle(Vector(135, 450), 50, ColorF::Aqua, 3);
	RENDER->DrawT(TEXT(" NPC\nICON"), 110, 420, ColorF::Aqua, 20);

	RENDER->DrawCircle(Vector(135, 250), 50, ColorF::Aqua, 3);
	RENDER->DrawT(TEXT(" NPC\nTalk Box"), 110, 230, ColorF::Aqua, 16);

	ItemListWnd();
	ItemStatWnd();

}

void ShopScene::ItemListWnd()
{
	//아이템 종류 목차
	RENDER->DrawRect(Vector(500, 235), Vector(400, 220), ColorF::OrangeRed);
	RENDER->DrawRect(Vector(368, 232), Vector(120, 180), ColorF::Tomato);
	RENDER->DrawT(TEXT("    ITEM\nWEAPON"), 328, 215, ColorF::Tomato, 20);

	RENDER->DrawRect(Vector(500, 232), Vector(120, 180), ColorF::Khaki);
	RENDER->DrawT(TEXT("  ITEM\nBULLET"), 465, 215, ColorF::Khaki, 20);

	RENDER->DrawRect(Vector(630, 232), Vector(120, 180), ColorF::HotPink);
	RENDER->DrawT(TEXT("      ITEM\nUSINGITEM"), 575, 215, ColorF::HotPink, 20);

	RENDER->DrawRect(Vector(500, 560),Vector(400, 430),ColorF::Red);
	RENDER->DrawLine(Vector(300, 408), Vector(700, 408), ColorF::Red);
	RENDER->DrawLine(Vector(300, 462), Vector(700, 462), ColorF::Red);
	RENDER->DrawLine(Vector(300, 524), Vector(700, 524), ColorF::Red);
	RENDER->DrawLine(Vector(300, 584), Vector(700, 584), ColorF::Red);
	RENDER->DrawLine(Vector(300, 644), Vector(700, 644), ColorF::Red);
	RENDER->DrawLine(Vector(300, 704),Vector(700, 704),ColorF::Red);

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
	RENDER->DrawRect(Vector(900, 450), Vector(400, 650), ColorF::Yellow);
	RENDER->DrawRect(Vector(900, 235), Vector(100, 100), ColorF::Aqua, 3);
	RENDER->DrawT(TEXT("ITEM\nICON"), 880, 215, ColorF::Aqua, 20);


	RENDER->DrawRect(Vector(910, 650), Vector(125, 35), ColorF::Aquamarine, 3);
	RENDER->DrawT(TEXT("수 량"), 890, 635, ColorF::Aquamarine, 20);

	RENDER->DrawT(TEXT("BUY"), 815, 688, ColorF::Aquamarine, 20);
	RENDER->DrawRect(Vector(975, 700), Vector(125, 35), ColorF::Aquamarine, 3);
	RENDER->DrawT(TEXT("나가기 F3"), 935, 686, ColorF::Aquamarine, 20);
	//RENDER->DrawT(TEXT("ITEM INFO"), 750, 400, ColorF::Red, 25);
}