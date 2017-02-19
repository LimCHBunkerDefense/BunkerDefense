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
//	RENDER->LoadImageFiles(TEXT("PistolIdle"), TEXT("Image/Item/Pistol/Idle/Idle"), TEXT("png"), 2);
//	RENDER->LoadImageFiles(TEXT("PistolShot"), TEXT("Image/Item/Pistol/Shot/Shot"), TEXT("png"), 3);
//	RENDER->LoadImageFiles(TEXT("ShotGunIdle"), TEXT("Image/Item/ShotGun/Idle/Idle"), TEXT("png"), 2);
//	RENDER->LoadImageFiles(TEXT("ShotGunShot"), TEXT("Image/Item/ShotGun/Shot/Shot"), TEXT("png"), 3);
//	RENDER->LoadImageFiles(TEXT("ShotGunReload"), TEXT("Image/Item/ShotGun/Reload/Reload"), TEXT("png"), 11);
//	RENDER->LoadImageFiles(TEXT("MachineGunIdle"), TEXT("Image/Item/MachineGun/Idle/Idle"), TEXT("png"), 2);
//	RENDER->LoadImageFiles(TEXT("MachineGunShot"), TEXT("Image/Item/MachineGun/Shot/Shot"), TEXT("png"), 7);
//	RENDER->LoadImageFiles(TEXT("LaserGunIdle"), TEXT("Image/Item/LaserGun/Idle/Idle"), TEXT("png"), 2);
//	RENDER->LoadImageFiles(TEXT("LaserGunShot"), TEXT("Image/Item/LaserGun/Shot/Shot"), TEXT("png"), 21);

	// ItemList에 Item Database 저장
	m_shopItemList.push_back(new Item(1001));
	m_shopItemList.push_back(new Item(1002));
	m_shopItemList.push_back(new Item(1003));
	m_shopItemList.push_back(new Item(1004));
	m_shopItemList.push_back(new Item(2001));
	m_shopItemList.push_back(new Item(2002));
	m_shopItemList.push_back(new Item(2003));
	m_shopItemList.push_back(new Item(2004));
	m_shopItemList.push_back(new Item(3001));
	m_shopItemList.push_back(new Item(3002));
	m_shopItemList.push_back(new Item(3003));
	m_shopItemList.push_back(new Item(3004));


}

ObjectManager::~ObjectManager()
{

}


void ObjectManager::Update(float deltaTime)
{
	m_pPlayer->Update(deltaTime);

	FOR_LIST(Object*, m_creatureList)
	{
		if ((*it)->IsDestroyed())
		{
			OBJECT->DestroyCreature((*it));
			break;
		}
		(*it)->Update(deltaTime);
	}

	m_bunker->Update(deltaTime);

	FOR_LIST(Object*, m_bulletList)
	{
		if ((*it)->UpdateBool(deltaTime))
		{
			OBJECT->DestroyBullet((*it));
			break;
		}
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
		if(SCENE->GetColliderOnOff()) pCamera->DrawRect((*it)->Collider().LeftTop(), (*it)->Collider().size, ColorF::Yellow, 3);
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

	float scale = 1.0;
	colSize = Vector(20, 20) * scale;
	anchor = Vector(0.5, 0.95f);

	m_pPlayer->Animation()->Register(IDLE_PISTOL, new Animation(TEXT("Idle_Pistol"), 2, 2, true, scale, anchor.x, anchor.y));
	m_pPlayer->Animation()->Register(SHOT_PISTOL, new Animation(TEXT("Attack_Pistol"), 4, 20, false, scale, anchor.x, anchor.y));
	m_pPlayer->Animation()->Register(IDLE_MACHINE, new Animation(TEXT("Idle_Machine"), 2, 2, true, scale, anchor.x, anchor.y));
	m_pPlayer->Animation()->Register(SHOT_MACHINE, new Animation(TEXT("Attack_Machine"), 8, 20, false, scale, anchor.x, anchor.y));
	m_pPlayer->Animation()->Register(IDLE_LASER, new Animation(TEXT("Idle_Laser"), 2, 2, true, scale, anchor.x, anchor.y));
	m_pPlayer->Animation()->Register(SHOT_LASER, new Animation(TEXT("Attack_Laser"), 22, 50, false, scale, anchor.x, anchor.y));
	m_pPlayer->Animation()->Register(IDLE_SHOT, new Animation(TEXT("Idle_Shot"), 2, 2, true, scale, anchor.x, anchor.y));
	m_pPlayer->Animation()->Register(SHOT_SHOT, new Animation(TEXT("Attack_Shot"), 4, 10, false, scale, anchor.x, anchor.y));
	m_pPlayer->Animation()->Register(RELOAD_SHOT, new Animation(TEXT("Reload_Shot"), 11, 2, false, scale, anchor.x, anchor.y));
	

}

void ObjectManager::DestroyPlayer()
{
	DELETE_OBJECT(m_pPlayer);
}




void ObjectManager::CreateCreature(OBJ_TAG tag, Vector pos)
{
	NEW_OBJECT(Object* pCreature, Creature(tag));
	pCreature->SetPosition_Creature(pos);
	pCreature->SetStartPos(pos);

	Vector colSize, anchor;
	float scale;
	switch (tag)
	{
	case OBJ_ENT:
		scale = 1.0;
		colSize = Vector(20, 20) * scale;
		anchor = Vector(0.5, 0.95f);
		pCreature->Animation()->Register(CREATURE_IDLE, new Animation(TEXT("EntIdle"), 2, 2, true, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_RUN, new Animation(TEXT("EntRun"), 21, 17, true, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_ATTACK, new Animation(TEXT("EntAttack"), 16, 8, false, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_DEAD, new Animation(TEXT("EntDie"), 7, 4, false, scale, anchor.x, anchor.y));
		break;
	case OBJ_LAVA:
		scale = 0.3;
		colSize = Vector(20, 20) * scale;
		anchor = Vector(0.5, 0.95f);
		pCreature->Animation()->Register(CREATURE_IDLE, new Animation(TEXT("LavaIdle"), 2, 2, true, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_RUN, new Animation(TEXT("LavaRun"), 23, 17, true, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_ATTACK, new Animation(TEXT("LavaAttack"), 21, 15, false, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_DEAD, new Animation(TEXT("LavaDie"), 13, 10, false, scale, anchor.x, anchor.y));
		break;
	case OBJ_DARKPRIEST:
		scale = 0.4;
		colSize = Vector(20, 20) * scale;
		anchor = Vector(0.5, 0.95f);
		pCreature->Animation()->Register(CREATURE_IDLE, new Animation(TEXT("DarkpriestIdle"), 2, 2, true, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_RUN, new Animation(TEXT("DarkpriestRun"), 16, 10, true, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_ATTACK, new Animation(TEXT("DarkpriestAttack"), 32, 17, false, scale, anchor.x, anchor.y));
		pCreature->Animation()->Register(CREATURE_DEAD, new Animation(TEXT("DarkpriestDie"), 23, 15, false, scale, anchor.x, anchor.y));
		break;
	}	

	pCreature->SetOriginScale(scale);
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
	
	// 아이템
//	switch (tag)
//	{
//	case ITEM_PISTOL:
//		pItem->Animation()->Register(GUN_IDLE, new Animation(TEXT("PistolIdle"), 2, 2, true, 1.0f, 0.5f, 1.0f));
//		pItem->Animation()->Register(GUN_SHOT, new Animation(TEXT("PistolShot"), 3, 3, false, 1.0f, 0.5f, 1.0f));
//		break;
//
//	case ITEM_SHOTGUN:
//		pItem->Animation()->Register(GUN_IDLE, new Animation(TEXT("ShotGunIdle"), 2, 2, true, 1.0f, 0.5f, 1.0f));
//		pItem->Animation()->Register(GUN_SHOT, new Animation(TEXT("ShotGunShot"), 3, 3, false, 1.0f, 0.5f, 1.0f));
//		pItem->Animation()->Register(GUN_RELOAD, new Animation(TEXT("ShotGunReload"), 11, 11, false, 1.0f, 0.5f, 1.0f));
//		break;
//
//	case ITEM_MACHINEGUN:
//		pItem->Animation()->Register(GUN_IDLE, new Animation(TEXT("MachineGunIdle"), 2, 2, true, 1.0f, 0.5f, 1.0f));
//		pItem->Animation()->Register(GUN_SHOT, new Animation(TEXT("MachineGunShot"), 7, 7, false, 1.0f, 0.5f, 1.0f));
//		break;	
//
//	case ITEM_LASERGUN:
//		pItem->Animation()->Register(GUN_IDLE, new Animation(TEXT("LaserGunIdle"), 2, 2, true, 1.0f, 0.5f, 1.0f));
//		pItem->Animation()->Register(GUN_SHOT, new Animation(TEXT("LaserGunShot"), 21, 21, false, 1.0f, 0.5f, 1.0f));
//		break;
//	}

	return pItem;
}

void ObjectManager::CreateBullet(OBJ_TAG tag, Vector pos, ITEM_TAG itemTag)
{
	NEW_OBJECT(Object* pBullet, Bullet(tag));
	pBullet->SetPosition_Creature(m_pPlayer->Position());	// 크리쳐랑 반대라 endPos 설정이라고 보면 됨
	pBullet->SetStartPos(pos);								// 크리쳐랑 반대라 endPos 설정이라고 보면 됨

	Vector colSize, anchor;
	float range;
	switch (itemTag)
	{
	case ITEM_PISTOL:
		colSize = Vector(10, 10);
		anchor = Vector(0.5, 0.95f);
		range = ITEM->GetData(itemTag)->range;
		pBullet->Animation()->Register(BULLET_IDLE, new Animation(TEXT("PSBulletIdle"), 1, 1, false, 1, anchor.x, anchor.y));
		pBullet->Animation()->Register(BULLET_EXPLODE, new Animation(TEXT("PSBulletExplode"), 1, 1, false, 1, anchor.x, anchor.y));
		break;
	case ITEM_MACHINEGUN:
		colSize = Vector(10, 10);
		anchor = Vector(0.5, 0.95f);
		range = ITEM->GetData(itemTag)->range;
		pBullet->Animation()->Register(BULLET_IDLE, new Animation(TEXT("MGBulletIdle"), 1, 1, false, 1, anchor.x, anchor.y));
		pBullet->Animation()->Register(BULLET_EXPLODE, new Animation(TEXT("MGBulletExplode"), 1, 1, false, 1, anchor.x, anchor.y));
		break;
	}
	
	pBullet->SetRange();
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

void ObjectManager::CreateGrenade(OBJ_TAG tag, Vector pos, GRENADE_STATE gre_state)
{
	NEW_OBJECT(Object* pBullet, Grenade(tag, gre_state));
	float m_t = GetSightHeight() / SIGHTHEIGHT_MAX;
	//Vector NewPos = pos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);
	pBullet->SetPosition_Creature(pos);
	pBullet->SetStartPos(pos);
	pBullet->SetGoal(m_t);

	Vector colSize, anchor;
	float scale = 0.5f;
	colSize = Vector(20, 20) * scale;
	anchor = Vector(0.5, 0.95f);

	switch (gre_state) {
	case GRENADE_IDLE:
		pBullet->Animation()->Register(gre_state, new Animation(TEXT("Grenade"), 1, 10, false, 0.2f, anchor.x, anchor.y));
		pBullet->Animation()->Register(GRENADE_EXPLODE, new Animation(TEXT("Explode"), 7, 3, false, 1.0f, anchor.x, anchor.y));
		break;
	case FLAME_IDLE:
		pBullet->Animation()->Register(gre_state, new Animation(TEXT("Flame_idle"), 1, 10, false, 0.2f, anchor.x, anchor.y));
		pBullet->Animation()->Register(FLAME_EXPLODE, new Animation(TEXT("Flame_Explode"), 30, 4, false, 1.0f, anchor.x, 0.7f));
		break;
	case AIRBOMB_IDLE:
		pBullet->Animation()->Register(gre_state, new Animation(TEXT("Plane_idle"), 1, 10, false, 0.2f, anchor.x, anchor.y));
		pBullet->Animation()->Register(AIRBOMB_EXPLODE, new Animation(TEXT("Plane_Explode"), 42, 10, false, 1.0f, anchor.x, 0));
		break;
	}
	

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