#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(OBJ_TAG tag) : Object(tag)
{
	CreatureData* pData = CREATURE->GetData(tag);
	m_scale = 1.0f;
	m_state = BULLET_IDLE;
	m_t = 0.0F;
	m_z = OBJECT->GetSightHeight();

	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{

}

BOOL Bullet::UpdateBool(float deltaTime)
{
	//�̵����⺤�� �ǽð� ������Ʈ
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
	
	// �÷��̾��� ī�޶� ȸ���� ���� StartPos ������Ʈ
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
	SetCollider(Collider().size * ((1 - m_t) *1.0f) / m_scale, Collider().anchor);
	SetScale((1 - m_t) *1.0f);
	m_scale = (1 - m_t) *1.0f;

	Vector gap = Vector(VIEW_WIDTH, VIEW_HEIGHT) - OBJECT->GetSightPos();
	pCamera->Draw3D(Animation()->Current()->GetSprite(), Vector(m_startPos.x, m_startPos.y), (1 - m_t), OBJECT->GetSightHeight(), m_state);
}


void Bullet::IdleState(float deltaTime) 
{
	Animation()->Play(BULLET_IDLE);

	// �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);

	// ũ���Ŀ� ���� �ݴ����
	Vector pos = GetNowPos();
	SetPosition_Creature(pos, pos * 5);

	// �����Ÿ� ������ �� m_t�� 1�ΰ�� Ȥ�� ũ���Ŀ� �浹ó�� �Ǹ� �Ѿ� ����
	if (m_t >= 0.9999 || Collided())
	{
		Animation()->Play(BULLET_EXPLODE);
		m_state = BULLET_EXPLODE;
	}
}

bool Bullet::ExplodeState(float deltaTime) 
{
	return true;
}

BOOL Bullet::Collided()
{
	list<Object*> creatureList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, creatureList) {
		if (abs(MATH->Angle(m_moveDirection, (*it)->GetMoveDirection())) < (*it)->GetCollideAngle()) {
			if (m_t + (*it)->GetMT() >= 1.0f) {
				if (MATH->IsCollided(this->Collider(), (*it)->Collider()))
				{
					int money = (*it)->GetMoney();
					OBJECT->GetPlayer()->AddMoney(money);
					int score = (*it)->GetScore();
					OBJECT->GetPlayer()->AddScore(score);
					Object* p = OBJECT->GetPlayer();
					OBJECT->DestroyCreature((*it));
					return true;
				}
			}
		}
	}
	return false;
}

// ī�޶� ȸ���� ���� StartPos ������Ʈ
void Bullet::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection * -1);
	angle += OBJECT->GetDeltaSightAngle();

	// �� p(0,0)�� �������� ������ ���ο� pos�� �÷��̾� ���� p'(MINI_WIDTH * 0.5, MINI_HEIGHT) �������� (*it)�� ��ǥ ����
	Vector pos = MATH->ToDirection(angle) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();

	m_startPos = pos;
}