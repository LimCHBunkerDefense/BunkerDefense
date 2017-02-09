#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(OBJ_TAG tag) : Object(tag)
{
	CreatureData* pData = CREATURE->GetData(tag);
	m_scale = 0.5f;
	m_state = BULLET_IDLE;
	m_t = 0.0F;
	m_moveSpeed = 0.1F;

	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
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

void Bullet::IdleState(float deltaTime) {
	// �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);

	// ũ���Ŀ� ���� �ݴ����
	Vector pos = m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1-m_t);
	SetPosition_Creature(pos, pos * 5);


	Animation()->Play(BULLET_IDLE);
}

void Bullet::HitState(float deltaTime) {

}

void Bullet::Draw(Camera* pCamera)
{
	SetCollider(Collider().size * ((1-m_t) *0.05f) / m_scale, Collider().anchor);
	SetScale((1-m_t) *0.05f);
	m_scale = (1 - m_t) *0.05f;

	pCamera->Draw3D(Animation()->Current()->GetSprite(), m_startPos, (1-m_t), OBJECT->GetSightHeight());
}