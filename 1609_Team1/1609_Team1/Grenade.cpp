#include "Grenade.h"



Grenade::Grenade()
{
}

Grenade::Grenade(OBJ_TAG tag) : Object(tag)
{
	//m_angle = 10;//���� ���� �����Ը� ����
	CreatureData* pData = CREATURE->GetData(tag);
	m_scale = 1.0f;
	m_state = BULLET_IDLE;
	m_t = 0.0F;
	m_moveSpeed = 0.5F;

	m_height = OBJECT->GetSightHeight();
	m_addHeight = 0;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Grenade::~Grenade()
{
}

//�ε����� �����ǰ� �ϱ� ���� BOOL �Լ� �߰�
BOOL Grenade::UpdateBool(float deltaTime) {
	BOOL result;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	switch (m_state)
	{
	case BULLET_IDLE: result = IdleState(deltaTime); break;
	case BULLET_EXPLODE: HitState(deltaTime); break;
	}

	Animation()->Update(deltaTime);
	return result;
}

void Grenade::Update(float deltaTime)
{
	//�̵����⺤�� �ǽð� ������Ʈ
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	switch (m_state)
	{
	case BULLET_IDLE: IdleState(deltaTime); break;
	case BULLET_EXPLODE: HitState(deltaTime); break;
	}

	Animation()->Update(deltaTime);
}

BOOL Grenade::IdleState(float deltaTime) {
	// �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);
	if (m_t == 1.0F) return true;

	// ũ���Ŀ� ���� �ݴ����
	Vector pos = m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);
	SetPosition_Creature(pos, pos * 5);



	Animation()->Play(BULLET_IDLE);
	if (Collided()) {
		return true;
	}
	return false;
}

BOOL Grenade::Collided()
{
	if (0 <= m_height && m_height <= 450.0f) {
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
void Grenade::HitState(float deltaTime) {

}

void Grenade::Draw(Camera* pCamera)
{
	SetCollider(Collider().size * ((1 - m_t) *1.0f) / m_scale, Collider().anchor);
	SetScale((1 - m_t) *1.0f);
	m_scale = (1 - m_t) *1.0f;

	Vector gap = Vector(VIEW_WIDTH, VIEW_HEIGHT) - OBJECT->GetAimPos();
	pCamera->Draw3D(Animation()->Current()->GetSprite(), Vector(m_startPos.x, m_startPos.y + m_addHeight), (1 - m_t), OBJECT->GetSightHeight() + m_addHeight, m_state);
}