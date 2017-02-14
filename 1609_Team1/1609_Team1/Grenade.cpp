#include "Grenade.h"



Grenade::Grenade()
{
}

Grenade::Grenade(OBJ_TAG tag) : Object(tag)
{
	//m_angle = 10;//���� ���� �����Ը� ����
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

//�ε����� �����ǰ� �ϱ� ���� BOOL �Լ� �߰�
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
	// �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);
	

	// ũ���Ŀ� ���� �ݴ����
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