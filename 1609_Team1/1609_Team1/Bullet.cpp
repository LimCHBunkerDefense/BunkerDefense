#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(OBJ_TAG tag) : Object(tag)
{
	m_scale = 1.0f;
	m_state = BULLET_IDLE;
	m_t = 0.0F;
	m_z = 600 - OBJECT->GetSightHeight();	// 화면 상하 이동 시 뒷 배경의 height가 하상으로 움직이기때문에 최대높이 600에서 sightHeight를 빼주도록 함

	m_attack = 1000;//OBJECT->GetPlayer()->GetCurrentItem()->GetAttack();
	m_moveSpeed = OBJECT->GetPlayer()->GetCurrentItem()->GetBulletSpeed();
	m_range = OBJECT->GetPlayer()->GetCurrentItem()->GetRange();
	m_moveDirection = Vector(Position() * -1 + m_startPos).Normalize();
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{

}

BOOL Bullet::UpdateBool(float deltaTime)
{
	//이동방향벡터 실시간 업데이트
	m_moveDirection = Vector(Position() * -1 + m_startPos).Normalize();
	
	// 플레이어의 카메라 회전에 의한 StartPos 업데이트
	StartPosUpdate();

	bool result = false;
	switch (m_state)
	{
		case BULLET_IDLE: IdleState(deltaTime); break;
		case BULLET_EXPLODE: result = ExplodeState(deltaTime); break;
	}

	Animation()->Update(deltaTime);

	return result;
}

void Bullet::Draw(Camera* pCamera)
{
	// SetCollider(Collider().size * ((1 - m_t) *1.0f) / m_scale, Collider().anchor);
	SetScale((1 - m_t) *1.0f);
	m_scale = (1 - m_t) *1.0f;

	Vector gap = Vector(VIEW_WIDTH, VIEW_HEIGHT) - OBJECT->GetSightPos();
	pCamera->Draw3D(Animation()->Current()->GetSprite(), Vector(m_startPos.x, m_startPos.y), (1 - m_t), OBJECT->GetSightHeight(), m_state, 1, m_z);
}


void Bullet::IdleState(float deltaTime) 
{
	//cout << Position().x << "   " << Position().y << "       " << m_t << endl;	총알 위치 디버깅용

	Animation()->Play(BULLET_IDLE);
	
	// 이동에 관계된 비율 (시작점에서 플레이어까지 가는 거리를 1로 봤을 때, 현재 이동한 거리의 비율)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime , 0.0f, 1.0f);

	// 크리쳐와 식이 반대로임
	Vector pos = m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);
	SetPosition_Creature(pos);

	// 사정거리 끝까지 간 m_t가 1인경우 혹은 크리쳐와 충돌처리 되면 총알 삭제
	if (m_t >= 0.9999 || Collided())
	{
		Animation()->Play(BULLET_EXPLODE);
		m_state = BULLET_EXPLODE;
	}
}

bool Bullet::ExplodeState(float deltaTime) 
{
	if(Animation()->Current()->GetCurrentIndex() == Animation()->Current()->GetSpriteCount() -1 )return true;
	return false;
}

BOOL Bullet::Collided()
{
	list<Object*> creatureList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, creatureList) 
	{
		// 크리쳐 충돌체와 충돌이 되고, z값 기준으로 높이가 맞아야 하고, m_t를 기준으로 거리가 맞아야 총에 맞은 것으로 간주 
		if (MATH->IsCollided(this->Collider(), (*it)->Collider())
			&& m_z <= (*it)->GetMaxZ()
			&& m_z >= (*it)->GetMinZ())
		{

			Object* p = OBJECT->GetPlayer();
			(*it)->AddCurrentLife(-m_attack);
			
			return true;
		}
	}
	return false;
}

// 카메라 회전에 의한 StartPos 업데이트. 실제로는 총알의 종료점
void Bullet::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection);
	angle += OBJECT->GetDeltaSightAngle();

	// 점 p(0,0)를 기준으로 구해진 새로운 pos를 플레이어 위지 p'(MINI_WIDTH * 0.5, MINI_HEIGHT) 기준으로 (*it)의 좌표 보정
	Vector pos = MATH->ToDirection(angle) * m_range + OBJECT->GetPlayer()->Position();

	m_startPos = pos;
}