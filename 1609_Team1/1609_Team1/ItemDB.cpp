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
	Add(new ItemData(ITEM_WEAPON, 1001, 10, 0, 5.0f, 0, 50,   0, 0,   TEXT("����(Pistol)"), 
		TEXT("�⺻ ���̴�. \n�������� ������ �� ����.")));
	
	// ���� ���� ����
	Add(new ItemData(ITEM_WEAPON, 1002, 30, 0, 10.0f, 0, 1000, 0, 2000, TEXT("�����(Machine Gun)"),
		TEXT("���簡 ������ �����. \n�ÿ��� Ÿ�ݰ��� ��ǰ�� ���̴�.")));
	Add(new ItemData(ITEM_WEAPON, 1003, 50, 0, 5.0f,  0, 700,  0, 1500, TEXT("ȭ�� ����(Fire Thrower)"),
		TEXT("�ٰŸ����� ��밡���� ȭ������. \n�ٰŸ����� ��û�� ȭ���� �ڶ��Ѵ�.")));
	Add(new ItemData(ITEM_WEAPON, 1004, 50, 0, 12.0f, 0, 1500, 0, 5000, TEXT("������ ��(Laser Gun)"), 
		TEXT("��û�� ��Ÿ��� �ڶ��ϴ� ��������. \n�ſ� ��� ���������� ������ �ӱݰ� �����ϱ⸦ ����!")));

	// ���� ���� ������(�Ѿ�)
	Add(new ItemData(ITEM_BULLET, 1005, 0, 0, 0, 0, 0, 10, 50, TEXT("���� ź��(Pistol Bullet)"),
		TEXT("������ ź����")));
	Add(new ItemData(ITEM_BULLET, 1006, 0, 0, 0, 0, 0, 100, 200, TEXT("����� ź��(Machine Gun Bullet)"),
		TEXT("������� ź����")));
	Add(new ItemData(ITEM_BULLET, 1007, 0, 0, 0, 0, 0, 50, 150, TEXT("ȭ�� ���� �⸧(Fire Thr' Oil)"),
		TEXT("ȭ�� ���� �⸧")));
	Add(new ItemData(ITEM_BULLET, 1008, 0, 0, 0, 0, 0, 100, 150, TEXT("������ �� ����(Laser Gun char')"),
		TEXT("������ �� ����")));

	// ���� ���� ������(�Ҹ�ǰ)
	Add(new ItemData(ITEM_USINGITEM, 1009, 100, 0, 5.0f,  0,   0, 0, 50,   TEXT("����ź(Grenade)"),
		TEXT("������ ������ ����ź. \n�տ� ���� ��� �ָ��� ������ ���Ѵ�.")));
	Add(new ItemData(ITEM_USINGITEM, 1010, 200, 0, 15.0f, 0,   0, 0, 3000, TEXT("���� ����(Air Bomb"),
		TEXT("�������ϰ� ����ϴ� ��������. \n������� ���θ� ȣ���ؼ� ������ ��û�Ѵ�.")));
	Add(new ItemData(ITEM_USINGITEM, 1011,  30, 0, 10.0f, 0,   0, 0, 1000, TEXT("�������(Rava Region)"),
		TEXT("�������� ȭ����¸� ������ �������. \n����� ��� ĸ���� ���� ������븦 �����Ѵ�.")));
	Add(new ItemData(ITEM_USINGITEM, 1012,   0, 0, 0.0f,  100, 0, 0, 200,  TEXT("��Ŀ ����(Bunker Repair)"),
		TEXT("���� �� ��Ŀ�� ����. ���ͷκ��� ���ݴ��� ���� �� ��Ŀ�� �����Ѵ�.")));


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