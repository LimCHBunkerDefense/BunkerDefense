#include "ObjectManager.h"
#include "Player.h"
#include "Creature.h"
#include "Bullet.h"

ObjectManager::ObjectManager()
{
	m_sightHeight = 400;
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

	FOR_LIST(Object*, m_bulletList)
	{
		if ((*it)->UpdateBool(deltaTime)) {
			OBJECT->DestroyBullet((*it));
			break;
		}
	}


}

void ObjectManager::Draw(Camera* pCamera)
{
	FOR_LIST(Object*, m_creatureList)
	{
		(*it)->Draw(pCamera);

		// �浹ü �����ִ� �κ��ε�, �̴ϸ��� ���� �����Ӱ� �������� �������� �ٸ��� ������ �浹ü �����ִ� ���� �ǹ̰� ����.
		if(SCENE->GetColliderOnOff()) pCamera->DrawRect((*it)->Collider().LeftTop(), (*it)->Collider().size, ColorF::Yellow, 3);
	}

	FOR_LIST(Object*, m_bulletList)
	{
		(*it)->Draw(pCamera);
		// �浹ü �����ִ� �κ��ε�, �̴ϸ��� ���� �����Ӱ� �������� �������� �ٸ��� ������ �浹ü �����ִ� ���� �ǹ̰� ����.
		if (SCENE->GetColliderOnOff()) pCamera->DrawRect((*it)->Collider().LeftTop(), (*it)->Collider().size, ColorF::Yellow, 3);
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
	switch (tag)
	{
	case OBJ_ENT:
		float scale = 0.5;
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

void ObjectManager::CreateBullet(OBJ_TAG tag, Vector pos)
{
	NEW_OBJECT(Object* pBullet, Bullet(tag));
	pBullet->SetPosition_Creature(pos, pos * 5);
	pBullet->SetStartPos(pos);

	Vector colSize, anchor;
	float scale = 0.05f;
	colSize = Vector(20, 20) * scale;
	anchor = Vector(0.5, 0.95f);
	pBullet->Animation()->Register(BULLET_IDLE, new Animation(TEXT("BulletIdle"), 1, 10, false, scale, anchor.x, anchor.y));
	//pBullet->Animation()->Register(BULLET_EXPLODE, new Animation(TEXT("EntRun"), 9, 7, true, scale, anchor.x, anchor.y));

	pBullet->SetCollider(colSize, anchor);

	m_bulletList.push_front(pBullet);
}

void ObjectManager::SetPosByDeltaAngle()
{
	float deltaPosX = 0;
	float deltaPosY = 0;

	if (abs(m_deltaSightAngle) > EPSILON)
	{
		// ũ���� ����Ʈ �ҷ��ٰ� �̴ϸ� ���� pos �������ִ� �κ�
		FOR_LIST(Object*, m_creatureList)
		{
			Object* pObj = (*it);
			float angle = MATH->Angle(Vector::Right(), (*it)->GetMoveDirection() * -1);
			angle += m_deltaSightAngle;

			// �� p(0,0)�� �������� ������ ���ο� pos�� �÷��̾� ���� p'(MINI_WIDTH * 0.5, MINI_HEIGHT) �������� (*it)�� ��ǥ ����
			//float x = MINI_WIDTH*0.5f + MATH->Cos(angle) * MINI_WIDTH * 0.5f;
			//float y = MINI_HEIGHT + MATH->Sin(angle) * MINI_WIDTH * 0.5f;

			Vector pos = MATH->ToDirection(angle) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();

			(*it)->SetStartPos(pos);
		}

		FOR_LIST(Object*, m_bulletList)
		{
			Object* pObj = (*it);
			float angle = MATH->Angle(Vector::Right(), (*it)->GetMoveDirection() * -1);
			angle += m_deltaSightAngle;

			Vector pos = MATH->ToDirection(angle) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();

			(*it)->SetStartPos(pos);
		}
		// ��� �¿� �̵��� ���� ��ȭ�� ���
		float sign = (m_deltaSightAngle > EPSILON) ? -1 : 1;
		deltaPosX = MATH->Tan(m_deltaSightAngle) * VIEW_WIDTH * 0.5 * sign;
	}


	// ī�޶� �̵��� ���� ��� ��� ��ġ ����
	//SCENE->GetScene(SCENE_PLAY)->SetPosBg(SCENE->GetScene(SCENE_PLAY)->GetPosBg() - Vector(deltaPosX, deltaPosY));

	

	// �þ� ��ȭ �� �ʱ�ȭ
	m_deltaSightAngle = 0;

	// ȭ�� ���� ��ȭ�� �ʱ�ȭ
	m_deltaSightHeight = 0;
	
}