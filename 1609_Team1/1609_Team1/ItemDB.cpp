#include "ItemDB.h"



ItemDB::ItemDB()
{
}


ItemDB::~ItemDB()
{
}

void ItemDB::Init()
{
	// �⺻ ����
	Add(new ItemData(ITEMTYPE_WEAPON, ITEM_PISTOL, 1001, 10, 0, 60.0f, 20.0f, 0, 60, 10,   1, 0,   TEXT("����(Pistol)"), 
		TEXT("�⺻ ���̴�. \n�������� ������ �� ����."), TEXT("��")));
	
	// ���� ���� ����
	Add(new ItemData(ITEMTYPE_WEAPON, ITEM_SHOTGUN, 1002, 80, 0, 50.0f, 25.0f, 0, 24, 2, 1, 1200, TEXT("����(Shot Gun)"),
		TEXT("�ٰŸ����� ��밡���� ����. \n �ٰŸ����� ��û�� ȭ���� �ڶ��Ѵ�."), TEXT("��")));
	Add(new ItemData(ITEMTYPE_WEAPON, ITEM_MACHINEGUN, 1003, 30, 0, 100.0f, 50.0f, 0, 2000, 500, 1, 2000, TEXT("�����(Machine Gun)"),
		TEXT("���簡 ������ �����. \n �ÿ��� Ÿ�ݰ��� ��ǰ�� ���̴�."), TEXT("��")));
	Add(new ItemData(ITEMTYPE_WEAPON, ITEM_LASERGUN, 1004, 50, 0, 120.0f, 120.0f, 0, 2000, 1000, 1, 5000, TEXT("������ ��(Laser Gun)"),
		TEXT("��û�� ��Ÿ��� �ڶ��ϴ� ��������. \n �ſ� ��� ���������� ������ �ӱ�\n�� �����ϱ⸦ ����!"), TEXT("�ֻ�")));

	// ���� ���� ������(�Ѿ�)
	Add(new ItemData(ITEMTYPE_BULLET, ITEM_PSBULLET, 2001, 0, 0, 0, 0, 0, 0, 0, 60, 10, TEXT("���� ź��(Pistol Bullet)"),
		TEXT("������ ź��")));
	Add(new ItemData(ITEMTYPE_BULLET, ITEM_SGBULLET, 2002, 0, 0, 0, 0, 0, 0, 0, 1800, 20, TEXT("���� ź��(Shot Gun Bullet)"),
		TEXT("���� ź��")));
	Add(new ItemData(ITEMTYPE_BULLET, ITEM_MGBULLET, 2003, 0, 0, 0, 0, 0, 0, 0, 2000, 15, TEXT("����� ź��(Machine Gun Bullet)"),
		TEXT("������� ź��")));
	Add(new ItemData(ITEMTYPE_BULLET, ITEM_LGBULLET, 2004, 0, 0, 0, 0, 0, 0, 0, 2000, 30, TEXT("������ �� ����(Laser Gun char')"),
		TEXT("������ �� ����")));

	// ���� ���� ������(�Ҹ�ǰ)
	Add(new ItemData(ITEMTYPE_USINGITEM, ITEM_GRENADE, 3001, 100, 0, 50.0f, 25.0f, 0,   0, 0, 10, 50,   TEXT("����ź(Grenade)"),
		TEXT("������ ������ ����ź. \n �տ� ���� ��� �ָ��� ������ ���Ѵ�.")));
	Add(new ItemData(ITEMTYPE_USINGITEM, ITEM_AIRBOMB, 3002, 200, 0, 120.0f, 60.0f, 0,   0, 0, 3, 3000, TEXT("���� ����(Air Bomb"),
		TEXT("�������ϰ� ����ϴ� ��������. \n������� ���θ� ȣ���ؼ� ������\n ��û�Ѵ�.")));
	Add(new ItemData(ITEMTYPE_USINGITEM, ITEM_RAVAREGION, 3003,  30, 0, 50.0f, 25.0f, 0,   0, 0, 5, 1000, TEXT("�������(Rava Region)"),
		TEXT("�������� ȭ����¸� ������ �������. \n ����� ��� ĸ���� ���� ������븦\n �����Ѵ�.")));
	Add(new ItemData(ITEMTYPE_USINGITEM, ITEM_BUNKERREPAIR, 3004,   0, 0, 0.0f, 0.0f,  100, 0, 0, 10, 200,  TEXT("��Ŀ ����(Bunker Repair)"),
		TEXT("���� �� ��Ŀ�� ����. ���ͷκ���\n ���ݴ��� ���� �� ��Ŀ�� �����Ѵ�.")));


	}

void ItemDB::Add(ItemData* pData)
{
	if (GetData(pData->itemID) == NULL)
	{
		m_pItems[pData->itemID] = pData;
	}
}

ItemData* ItemDB::GetData(int itemID)
{
	if (m_pItems.find(itemID) != m_pItems.end())
	{
		return m_pItems[itemID];
	}
	return NULL;
}