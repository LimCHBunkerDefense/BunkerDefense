#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(OBJ_TAG tag) : Object(tag)
{
	//m_angle = 10;//각도 내의 적에게만 반응
	CreatureData* pData = CREATURE->GetData(tag);
	m_scale = 1.0f;
	m_state = BULLET_IDLE;
	m_t = 0.0F;
	m_moveSpeed = 0.5F;

	m_height = OBJECT->GetSightHeight();
	m_addHeight = 100;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Bullet::~Bullet()
{
}

//부딪히면 삭제되게 하기 위해 BOOL 함수 추가
BOOL Bullet::UpdateBool(float deltaTime) {
	BOOL result;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	switch (m_state)
	{
		case BULLET_IDLE: result=IdleState(deltaTime); break;
		case BULLET_EXPLODE: HitState(deltaTime); break;
	}

	Animation()->Update(deltaTime);
	return result;
}

void Bullet::Update(float deltaTime)
{
	//이동방향벡터 실시간 업데이트
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	switch (m_state)
	{
		case BULLET_IDLE: IdleState(deltaTime); break;
		case BULLET_EXPLODE: HitState(deltaTime); break;
	}

	Animation()->Update(deltaTime);
}

BOOL Bullet::IdleState(float deltaTime) {
	// 이동에 관계된 비율 (시작점에서 플레이어까지 가는 거리를 1로 봤을 때, 현재 이동한 거리의 비율)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);
	if (m_t == 1.0F) return true;

	// 크리쳐와 식이 반대로임
	Vector pos = m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1-m_t);
	SetPosition_Creature(pos, pos * 5);

	

	Animation()->Play(BULLET_IDLE);
	if (Collided()) {
		return true;
	}
	return false;
}

BOOL Bullet::Collided()
{
	if (0<=m_height && m_height <= 350.0f) {
		list<Object*> creatureList = OBJECT->GetCreatureList();
		FOR_LIST(Object*, creatureList) {
			if (abs(MATH->Angle(m_moveDirection, (*it)->GetMoveDirection())) < (*it)->GetCollideAngle()) {
				if (m_t + (*it)->GetMT() >= 1.0f) {
					if (MATH->IsCollided(this->Collider(), (*it)->Collider()))
					{
						OBJECT->DestroyCreature((*it));
						return true;
					}
				}
			}
		}
	}
	return false;
}
void Bullet::HitState(float deltaTime) {

}

void Bullet::Draw(Camera* pCamera)
{
	SetCollider(Collider().size * ((1-m_t) *1.0f) / m_scale, Collider().anchor);
	SetScale((1-m_t) *1.0f);
	m_scale = (1 - m_t) *1.0f;

	pCamera->Draw3D(Animation()->Current()->GetSprite(), Vector(m_startPos.x, m_startPos.y+ m_addHeight), (1-m_t), OBJECT->GetSightHeight()+m_addHeight, m_state);
}