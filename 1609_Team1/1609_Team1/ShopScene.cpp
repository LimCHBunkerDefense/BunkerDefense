#include "ShopScene.h"

ShopScene::ShopScene()
{
	RENDER->LoadImageFile(TEXT("shopBG"), TEXT("Image/BackGround/shopBG.png"));
	RENDER->LoadImageFile(TEXT("shopNPC"), TEXT("Image/NPC/shopnpc2.png"));
	RENDER->LoadImageFile(TEXT("talkBox"), TEXT("Image/NPC/talk_box.png"));
	//m_itemList.push_back();

	// itemDB ����
	ITEM->Init();

	// ItemList�� Item Database ����
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

	// BoxList�� Box Database ����
	AddBoxList(new Box(BUTTON_WEAPON, Vector(420, 235), Vector(120, 180)));
	AddBoxList(new Box(BUTTON_BULLET, Vector(550, 235), Vector(120, 180)));
	AddBoxList(new Box(BUTTON_USINGITEM, Vector(680, 235), Vector(120, 180)));

	AddBoxList(new Box(BUTTON_FIRST, Vector(550, 375), Vector(400, 60)));  // �Һз� �����۵� - index 3����
	AddBoxList(new Box(BUTTON_SECOND, Vector(550, 435), Vector(400, 60)));
	AddBoxList(new Box(BUTTON_THIRD, Vector(550, 495), Vector(400, 60)));
	AddBoxList(new Box(BUTTON_FORTH, Vector(550, 555), Vector(400, 60)));

	AddBoxList(new Box(BUTTON_BUY, Vector(885, 700), Vector(125, 35)));	// ���� ��ư �ڽ�

	IsWeaponClicked = false;
	IsBulletClicked = false;
	IsUsingItemClicked = false;	
}


ShopScene::~ShopScene()
{
	// �� ����� ���� �ʱ�ȭ
	//GetBoxList().clear();
	//m_itemList.clear();
	//m_selectedItem = NULL;
}

void ShopScene::OnEnter()
{
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("shopBG")), 1.0f, 0, 0));
	NEW_OBJECT(m_pNpcIcon, Sprite(RENDER->GetImage(TEXT("shopNPC")), 1.3f, 0, 0));
	NEW_OBJECT(m_pTalkBox, Sprite(RENDER->GetImage(TEXT("talkBox")), 0.55, 0, 0));

	// ���콺 Ŀ�� ���̰�
	ShowCursor(true);
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
	pMainCamera->Draw(m_pTalkBox, Vector(15, 85)); // talkbox image
	pMainCamera->Draw(m_pNpcIcon, Vector(-138, 250)); // npc image

	RENDER->DrawRect(Vector(670, 50), Vector (150, 50), ColorF::BlanchedAlmond);
	RENDER->DrawT(TEXT("SHOP"), 640, 35, ColorF::BlanchedAlmond, 25);
	RENDER->DrawRect(Vector(950, 450),Vector(320, 300),ColorF::AntiqueWhite, 3);
	RENDER->DrawT(TEXT("-������ ����-"), 880, 335, ColorF::BlanchedAlmond, 20);
	//pMainCamera->DrawT(TEXT("ATK:"), 800, 495, ColorF::AntiqueWhite, 15);
	if (m_selectedItem != NULL)
	{
		pMainCamera->DrawT(m_selectedItem->GetName(), 870, 395, ColorF::AntiqueWhite, 15);
		pMainCamera->DrawT(m_selectedItem->GetInfo(), 830, 420, ColorF::AntiqueWhite, 15);
		
		// float �� ����ؼ� text ���
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

void ShopScene::ItemListWnd()
{
	//������ ���� ����
	RENDER->DrawRect(Vector(550, 235), Vector(400, 220), ColorF::OrangeRed);
	RENDER->DrawRect(Vector(418, 232), Vector(120, 180), ColorF::Tomato);
	RENDER->DrawT(TEXT("    ITEM\nWEAPON"), 378, 215, ColorF::Tomato, 20);

	RENDER->DrawRect(Vector(550, 232), Vector(120, 180), ColorF::Khaki);
	RENDER->DrawT(TEXT("  ITEM\nBULLET"), 515, 215, ColorF::Khaki, 20);

	RENDER->DrawRect(Vector(680, 232), Vector(120, 180), ColorF::HotPink);
	RENDER->DrawT(TEXT("      ITEM\nUSINGITEM"), 625, 215, ColorF::HotPink, 20);

	RENDER->DrawRect(Vector(550, 560),Vector(400, 430),ColorF::Red);
	RENDER->DrawLine(Vector(350, 408), Vector(750, 408), ColorF::Red);
	RENDER->DrawLine(Vector(350, 462), Vector(750, 462), ColorF::Red);
	RENDER->DrawLine(Vector(350, 524), Vector(750, 524), ColorF::Red);
	RENDER->DrawLine(Vector(350, 584), Vector(750, 584), ColorF::Red);
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
	//���� ������ ����
	RENDER->DrawRect(Vector(950, 450), Vector(400, 650), ColorF::Yellow);
	RENDER->DrawRect(Vector(950, 235), Vector(100, 100), ColorF::Aqua, 3);
	RENDER->DrawT(TEXT("ITEM\nICON"), 930, 215, ColorF::Aqua, 20);


	RENDER->DrawRect(Vector(940, 650), Vector(125, 35), ColorF::Aquamarine, 3);
	RENDER->DrawT(TEXT("�� ��"), 920, 635, ColorF::Aquamarine, 20);

	RENDER->DrawT(TEXT("BUY"), 860, 688, ColorF::Aquamarine, 20);
	RENDER->DrawRect(Vector(1025, 700), Vector(125, 35), ColorF::Aquamarine, 3);
	RENDER->DrawT(TEXT("������ F3"), 985, 686, ColorF::Aquamarine, 20);
	//RENDER->DrawT(TEXT("ITEM INFO"), 750, 400, ColorF::Red, 25);
}