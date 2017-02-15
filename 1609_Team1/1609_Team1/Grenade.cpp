#include "Grenade.h"



Grenade::Grenade()
{
}

Grenade::Grenade(OBJ_TAG tag) : Object(tag)
{
	//m_angle = 10;//각도 내의 적에게만 반응
	CreatureData* pData = CREATURE->GetData(tag);
	m_scale = 1.0f;
	m_state = GRENADE_IDLE;
	m_t = 0.0F;
	m_moveSpeed = 0.5F;
	m_explodetime = 0.0F;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Grenade::~Grenade()
{
}

//부딪히면 삭제되게 하기 위해 BOOL 함수 추가
BOOL Grenade::UpdateBool(float deltaTime) {
	// 플레이어의 카메라 회전에 의한 StartPos 업데이트
	StartPosUpdate();

	BOOL result=false;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	// 크리쳐와 식이 반대로임
	Vector pos = m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);
	SetPosition_Creature(pos, pos * 5);

	switch (m_state)
	{
		case GRENADE_IDLE: IdleState(deltaTime); break;
		case GRENADE_EXPLODE: result = HitState(deltaTime); break;
	}

	Animation()->Update(deltaTime);
	return result;
}

void Grenade::Update(float deltaTime)
{
}

void Grenade::IdleState(float deltaTime) {
	
	// 이동에 관계된 비율 (시작점에서 플레이어까지 가는 거리를 1로 봤을 때, 현재 이동한 거리의 비율)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);
	

	Animation()->Play(GRENADE_IDLE);
	if (m_t == 1.0F) m_state = GRENADE_EXPLODE;
	
}

void Grenade::Collided()
{
	list<Object*> creatureList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, creatureList) {
		if (MATH->Distance(Position(), (*it)->GetNowPos())<= GRENADE_SIZE){
			OBJECT->DestroyCreature((*it));
		}
	}
}
BOOL Grenade::HitState(float deltaTime) {
	m_explodetime = MATH->Clamp(m_explodetime + m_moveSpeed * deltaTime, 0.0f, 1.0f);
	Animation()->Play(GRENADE_EXPLODE);
	if (m_explodetime <= 1.0)	return false;
	return true;
}

void Grenade::Draw(Camera* pCamera)
{
	SetCollider(Collider().size * ((1 - m_t) *1.0f) / m_scale, Collider().anchor);
	SetScale((1 - m_t) *1.0f);
	m_scale = (1 - m_t) *1.0f;

	//Vector gap = Vector(VIEW_WIDTH, VIEW_HEIGHT) - OBJECT->GetAimPos();
	pCamera->Draw3D(Animation()->Current()->GetSprite(), Vector(m_startPos.x, m_startPos.y), (1 - m_t), OBJECT->GetSightHeight(), m_state);
}

// 카메라 회전에 의한 StartPos 업데이트
void Grenade::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection * -1);
	angle += OBJECT->GetDeltaSightAngle();

	// 점 p(0,0)를 기준으로 구해진 새로운 pos를 플레이어 위지 p'(MINI_WIDTH * 0.5, MINI_HEIGHT) 기준으로 (*it)의 좌표 보정
	Vector pos = MATH->ToDirection(angle) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();

	m_startPos = pos;
}