#include "Bullet.h"



Bullet::Bullet()
{
	m_dir = DIRECTION_CENTER;
	m_moveDirection = Vector::Up();
}

Bullet::Bullet(OBJ_TAG tag) : Object(tag)
{
	CreatureData* pData = CREATURE->GetData(tag);
	m_dir = DIRECTION_CENTER;

	m_scale = 0.5f;
	m_moveSpeed = pData->moveSpeed;

	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
	// 크리쳐 이동방향벡터 실시간 업데이트
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	Animation()->Update(deltaTime);
}

void Bullet::Draw(Camera* pCamera)
{
	pCamera->Draw3D(Animation()->Current()->GetSprite(), Position(), m_dir, OBJECT->GetSightHeight());
}