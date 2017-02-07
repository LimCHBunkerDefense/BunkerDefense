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
	Add(new ItemData(ITEM_WEAPON, 1001, 10, 0, 0, 50,   0, 0,   TEXT("����")));
	
	// ���� ���� ����
	Add(new ItemData(ITEM_WEAPON, 1002, 30, 0, 0, 1000, 0, 2000, TEXT("�����")));
	Add(new ItemData(ITEM_WEAPON, 1003, 50, 0, 0, 700,  0, 1500, TEXT("ȭ�� ����")));
	Add(new ItemData(ITEM_WEAPON, 1004, 50, 0, 0, 1500, 0, 5000, TEXT("������ ��")));

	// ���� ���� ������
	Add(new ItemData(ITEM_WEAPON, 1005, 100, 0, 0,   0, 0, 50,   TEXT("����ź")));
	Add(new ItemData(ITEM_WEAPON, 1006, 200, 0, 0,   0, 0, 3000, TEXT("���� ����")));
	Add(new ItemData(ITEM_WEAPON, 1007,  30, 0, 0,   0, 0, 1000, TEXT("�������")));
	Add(new ItemData(ITEM_HEAL,   1008,   0, 0, 100, 0, 0, 200,  TEXT("��Ŀ ����")));

	Add(new ItemData(ITEM_BULLET, 1009, 0, 0, 0, 0, 10,  50,  TEXT("���� ź��")));
	Add(new ItemData(ITEM_BULLET, 1010, 0, 0, 0, 0, 100, 200, TEXT("����� ź��")));
	Add(new ItemData(ITEM_BULLET, 1011, 0, 0, 0, 0, 50,  150, TEXT("ȭ�� ���� �⸧")));
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