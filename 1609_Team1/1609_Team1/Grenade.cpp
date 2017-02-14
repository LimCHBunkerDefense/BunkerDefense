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
	m_goal = 0.5;
	m_moveSpeed = 0.5F;

	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Grenade::~Grenade()
{
}

//부딪히면 삭제되게 하기 위해 BOOL 함수 추가
BOOL Grenade::UpdateBool(float deltaTime) {
	BOOL result=false;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

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
	

	// 크리쳐와 식이 반대로임
	Vector pos = m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);
	SetPosition_Creature(pos, pos * 5);

	Animation()->Play(GRENADE_IDLE);
	if (m_t <= m_goal) m_state=GRENADE_EXPLODE;
}

BOOL Grenade::Collided()
{
	list<Object*> creatureList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, creatureList) {
		if (MATH->Distance(Position(), (*it)->GetNowPos())<= GRENADE_SIZE){
			OBJECT->DestroyCreature((*it));
			return true;
		
		}
	}
	return false;
}
BOOL Grenade::HitState(float deltaTime) {
	Animation()->Play(BULLET_EXPLODE);
	if (Collided()) {
		return true;
	}
	return false;
}

void Grenade::Draw(Camera* pCamera)
{
	SetCollider(Collider().size * ((1 - m_t) *1.0f) / m_scale, Collider().anchor);
	SetScale((1 - m_t) *1.0f);
	m_scale = (1 - m_t) *1.0f;

	Vector gap = Vector(VIEW_WIDTH, VIEW_HEIGHT) - OBJECT->GetAimPos();
	pCamera->Draw3D(Animation()->Current()->GetSprite(), Vector(m_startPos.x, m_startPos.y), (1 - m_t), OBJECT->GetSightHeight(), m_state);
}