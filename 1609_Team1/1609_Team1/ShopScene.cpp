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
		
	ItemListWnd();
	ItemStatWnd();
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
	
	if (SCENE->GetColliderOnOff())
	{
		list<Box*> boxList = GetBoxList();
		FOR_LIST(Box*, boxList)
		{
			RENDER->DrawRect((*it)->LeftTop() + (*it)->size * 0.5f, (*it)->size, ColorF::Yellow, 3.0f);
		}
	}

	list<Item*> itemList = SCENE->GetScene(SCENE_SHOP)->GetItemList();
	int index = 0;
	Item* pItem;

	switch (m_currentButton)
	{
	case BUTTON_WEAPON:
		FOR_LIST(Item*, itemList)
		{
			index++;
			pItem = ((*it)->GetTag() == ITEM_WEAPON) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 480, 350 + index * 50, ColorF::Yellow, 20.0f);
			}
		}
		break;
	case BUTTON_BULLET:
		FOR_LIST(Item*, itemList)
		{
			index++;
			pItem = ((*it)->GetTag() == ITEM_BULLET) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 480, 350 + index * 50, ColorF::Yellow, 20.0f);
			}
		}
		break;
	case BUTTON_USINGITEM:
		FOR_LIST(Item*, itemList)
		{
			index++;
			pItem = ((*it)->GetTag() == ITEM_USINGITEM) ? (*it) : NULL;
			if (pItem != NULL)
			{
				RENDER->DrawT(pItem->GetName(), 480, 350 + index * 50, ColorF::Yellow, 20.0f);
			}
		}
		break;
	}

}

void ShopScene::ItemListWnd()
{
	RENDER->DrawRect(Vector(500, 235), Vector(400, 220), ColorF::OrangeRed);
	RENDER->DrawRect(Vector(500, 560),Vector(400, 430),ColorF::Red);
	RENDER->DrawT(TEXT("ITEM LIST"), 430, 550, ColorF::Red, 25);
}
void ShopScene::ItemStatWnd()
{
	RENDER->DrawRect(Vector(900, 450), Vector(400, 650), ColorF::Yellow);
	RENDER->DrawRect(Vector(900, 250), Vector(150, 150), ColorF::Aqua, 3);
	RENDER->DrawT(TEXT("ITEM\nICON"), 880, 230, ColorF::Aqua, 20);

	RENDER->DrawRect(Vector(835, 700), Vector(125, 35), ColorF::Aquamarine, 3);
	RENDER->DrawT(TEXT("BUY"), 815, 688, ColorF::Aquamarine, 20);
	RENDER->DrawRect(Vector(975, 700), Vector(125, 35), ColorF::Aquamarine, 3);
	RENDER->DrawT(TEXT("나가기 F3"), 935, 686, ColorF::Aquamarine, 20);
	//RENDER->DrawT(TEXT("ITEM INFO"), 750, 400, ColorF::Red, 25);
}