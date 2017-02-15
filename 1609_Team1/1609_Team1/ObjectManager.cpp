#include "ObjectManager.h"
#include "Player.h"
#include "Creature.h"
#include "Item.h"
#include "Bullet.h"
#include "Grenade.h"
#include "Bunker.h"

ObjectManager::ObjectManager()
{
	m_sightHeight = SIGHTHEIGHT_DEFAULT;
	m_sight = Vector(0,0);

	// 플레이어 총 이미지 맵으로 저장
	RENDER->LoadImageFiles(TEXT("PistolIdle"), TEXT("Image/Item/Pistol/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("PistolShot"), TEXT("Image/Item/Pistol/Attack/Attack"), TEXT("png"), 3);

	// ItemList에 Item Database 저장
	m_shopItemList.push_back(new Item(1001));
	m_shopItemList.push_back(new Item(1002));
	m_shopItemList.push_back(new Item(1003));
	m_shopItemList.push_back(new Item(1004));
	m_shopItemList.push_back(new Item(1005));
	m_shopItemList.push_back(new Item(1006));
	m_shopItemList.push_back(new Item(1007));
	m_shopItemList.push_back(new Item(1008));
	m_shopItemList.push_back(new Item(1009));
	m_shopItemList.push_back(new Item(1010));
	m_shopItemList.push_back(new Item(1011));
	m_shopItemList.push_back(new Item(1012));


}

ObjectManager::~ObjectManager()
{

}


void ObjectManager::Update(float deltaTime)
{
	m_pPlayer->Update(deltaTime);

	FOR_LIST(Object*, m_creatureList)
	{
		(*it)->Update(deltaTime);
	}

	m_bunker->Update(deltaTime);

	FOR_LIST(Object*, m_bulletList)
	{
		(*it)->Update(deltaTime);
	}

	FOR_LIST(Object*, m_grenadeList)
	{
		if ((*it)->UpdateBool(deltaTime))
		{
			OBJECT->DestroyGrenade((*it));
			break;
		}
	}

	// 카메라 회전에 의한 맵 표시 좌표 업데이트 및 각도와 높이 변화값 초기화
	SetPosByDeltaAngle(deltaTime);
}

void ObjectManager::Draw(Camera* pCamera)
{
	FOR_LIST(Object*, m_creatureList)
	{
		(*it)->Draw(pCamera);

		// 충돌체 보여주는 부분인데, 미니맵의 실제 움직임과 보여지는 움직임이 다르기 때문에 충돌체 보여주는 것이 의미가 없음.
		//if(SCENE->GetColliderOnOff()) pCamera->DrawRect((*it)->Collider().LeftTop(), (*it)->Collider().size, ColorF::Yellow, 3);
	}

	FOR_LIST(Object*, m_bulletList)
	{
		(*it)->Draw(pCamera);
		
		// 충돌체 보여주는 부분인데, 미니맵의 실제 움직임과 보여지는 움직임이 다르기 때문에 충돌체 보여주는 것이 의미가 없음.
		//if (SCENE->GetColliderOnOff()) pCamera->DrawRect((*it)->Collider().LeftTop(), (*it)->Collider().size, ColorF::Yellow, 3);
	}

	FOR_LIST(Object*, m_grenadeList)
	{
		(*it)->Draw(pCamera);
	}

	m_pPlayer->Draw(pCamera);
}

void ObjectManager::CreatePlayer(Vector pos, Vector colSize, Vector anchor)
{
	NEW_OBJECT(m_pPlayer, Player(OBJ_PLAYER));
	m_pPlayer->SetPosition(pos);
	m_pPlayer->SetCollider(colSize, anchor);

}

void ObjectManager::DestroyPlayer()
{
	DELETE_OBJECT(m_pPlayer);
}




void ObjectManager::CreateCreature(OBJ_TAG tag, Vector pos)
{
	NEW_OBJECT(Object* pCreature, Creature(tag));
	pCreature->SetPosition_Creature(pos, pos * 5);
	pCreature->SetStartPos(pos);

	Vector colSize, anchor;
	float scale;
	switch (tag)
	{
	case OBJ_ENT:
		scale = 0.5;
		colSize = Vector(200, 300) * scale;
		anchor = Vector(0.5, 0.95f);
		pCreature->Animation()->Register(CREATURE_IDLE, new Animation(TEXT("EntIdle"), 2, 2, true, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_RUN, new Animation(TEXT("EntRun"), 9, 7, true, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_ATTACK, new Animation(TEXT("EntAttack"), 6, 3, false, scale, anchor.x, anchor.y));
		// pCreture->Animation()->Register(CREATURE_DEAD, new Animation(TEXT("EntDead"), 2, 10, false, 2.0f, anchor.x, anchor.y));
		break;
	}	

	pCreature->SetCollider(colSize, anchor);
	
	m_creatureList.push_front(pCreature);
}

void ObjectManager::DestroyCreature(Object* pCreature)
{
	m_creatureList.remove(pCreature);
	DELETE_OBJECT(pCreature);
}

void ObjectManager::DestroyAllCreature()
{
	FOR_LIST(Object*, m_creatureList)
	{
		DELETE_OBJECT((*it));
	}
	m_creatureList.clear();
}


Object* ObjectManager::CreateItem(ITEM_TAG tag, int itemID)
{
	NEW_OBJECT(Object* pItem, Item(itemID));
	 
	switch (tag)
	{
	case ITEM_PISTOL:
	// 	pItem->Animation()->Register(GUN_IDLE, new Animation(TEXT("PistolIdle"), 2, 2, true, 1.0f, 0.5f, 1.0f));
	// 	pItem->Animation()->Register(GUN_SHOT, new Animation(TEXT("PistolShot"), 3, 3, false, 1.0f, 0.5f, 1.0f));
	//  pItem->Animation()->Register(GUN_RELOAD, new Animation(TEXT("PistolReload"), 6, 3, false, 1.0f, 0.5f, 1.0f));
		break;
	
	case ITEM_MACHINEGUN:
		break;
	
	case ITEM_FIRETHROWER:
		break;
	
	case ITEM_LASERGUN:
		break;
	}

	return pItem;
}

void ObjectManager::CreateBullet(OBJ_TAG tag, Vector pos, ITEM_TAG itemTag)
{
	NEW_OBJECT(Object* pBullet, Bullet(tag));
	pBullet->SetPosition_Creature(pos, pos * 5);
	pBullet->SetStartPos(pos);

	Vector colSize, anchor;
	float scale;
	switch (itemTag)
	{
	case ITEM_PISTOL:
		scale = 0.05f;
		colSize = Vector(20, 20) * scale;
		anchor = Vector(0.5, 0.95f);
		pBullet->Animation()->Register(BULLET_IDLE, new Animation(TEXT("BulletIdle"), 1, 10, false, scale, anchor.x, anchor.y));
		//pBullet->Animation()->Register(BULLET_EXPLODE, new Animation(TEXT("EntRun"), 9, 7, true, scale, anchor.x, anchor.y));
		pBullet->SetMoveSpeed(5.0f);
		break;
	}
	

	pBullet->SetCollider(colSize, anchor);

	m_bulletList.push_front(pBullet);
}

void ObjectManager::DestroyAllBullet()
{
	FOR_LIST(Object*, m_bulletList)
	{
		DELETE_OBJECT((*it));
	}
	m_bulletList.clear();
}

void ObjectManager::DestroyBullet(Object* pCreature)
{
	m_bulletList.remove(pCreature);
	DELETE_OBJECT(pCreature);
}

void ObjectManager::CreateBunker() 
{
	m_bunker = new Bunker(OBJ_BUNKER); 

}

void ObjectManager::DestroyBunker() 
{ 
	if (m_bunker != NULL) delete m_bunker; m_bunker = NULL; 
}

void ObjectManager::CreateGrenade(OBJ_TAG tag, Vector pos)
{
	NEW_OBJECT(Object* pBullet, Grenade(tag));
	float m_t = GetSightHeight() / SIGHTHEIGHT_MAX;
	//Vector NewPos = pos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);
	pBullet->SetPosition_Creature(pos, pos * 5);
	pBullet->SetStartPos(pos);
	pBullet->SetGoal(m_t);

	Vector colSize, anchor;
	float scale = 0.5f;
	colSize = Vector(20, 20) * scale;
	anchor = Vector(0.5, 0.95f);
	pBullet->Animation()->Register(GRENADE_IDLE, new Animation(TEXT("Grenade"), 1, 10, false, 0.2f, anchor.x, anchor.y));
	pBullet->Animation()->Register(GRENADE_EXPLODE, new Animation(TEXT("Explode"), 7, 3,false, 100.0f, anchor.x, anchor.y));

	pBullet->SetCollider(colSize, anchor);

	m_grenadeList.push_front(pBullet);
}


void ObjectManager::DestroyGrenade(Object* pCreature)
{
	m_grenadeList.remove(pCreature);
	DELETE_OBJECT(pCreature);
}

void ObjectManager::DestroyAllGrenade()
{
	FOR_LIST(Object*, m_grenadeList)
	{
		DELETE_OBJECT((*it));
	}
	m_grenadeList.clear();
}
// 카메라 회전에 의한 맵 표시 좌표 업데이트 및 각도와 높이 변화값 초기화
void ObjectManager::SetPosByDeltaAngle(float deltaTime)
{
	float deltaPosX = 0;
	float deltaPosY = 0;

	// 배경 좌우 이동을 위한 변화량 계산, 곱하기 0.1은 구한 x좌표에 의한 스프라이트 그려지는 위치가 중앙선으로부터 너무 멀어져서 보정해준 값
	deltaPosX = VIEW_WIDTH * m_deltaSightAngle / CAMERA_ANGLE;
	

	// 카메라 이동에 따른 배경 출력 위치 변경
	m_sight = Vector(m_sight.x - deltaPosX, m_sightHeight);
	if (m_sight.x > 1920 * 2 * 1.8) m_sight -= Vector(1920 * 2 * 1.8, 0);
	if (m_sight.x < 1920 * 2 * 1.8 * -1) m_sight += Vector(1920 * 2 * 1.8, 0);

	// 시야 변화 각 초기화
	m_deltaSightAngle = 0;

	// 화면 높이 변화량 초기화
	m_deltaSightHeight = 0;
	
}