#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(OBJ_TAG tag) : Object(tag)
{
	m_scale = 1.0f;
	m_state = BULLET_IDLE;
	m_t = 0.0F;
	m_z = 600 - OBJECT->GetSightHeight();	// ȭ�� ���� �̵� �� �� ����� height�� �ϻ����� �����̱⶧���� �ִ���� 600���� sightHeight�� ���ֵ��� ��

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
	//�̵����⺤�� �ǽð� ������Ʈ
	m_moveDirection = Vector(Position() * -1 + m_startPos).Normalize();
	
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
	// SetCollider(Collider().size * ((1 - m_t) *1.0f) / m_scale, Collider().anchor);
	SetScale((1 - m_t) *1.0f);
	m_scale = (1 - m_t) *1.0f;

	Vector gap = Vector(VIEW_WIDTH, VIEW_HEIGHT) - OBJECT->GetSightPos();
	pCamera->Draw3D(Animation()->Current()->GetSprite(), Vector(m_startPos.x, m_startPos.y), (1 - m_t), OBJECT->GetSightHeight(), m_state, 1, m_z);
}


void Bullet::IdleState(float deltaTime) 
{
	//cout << Position().x << "   " << Position().y << "       " << m_t << endl;	�Ѿ� ��ġ ������

	Animation()->Play(BULLET_IDLE);
	
	// �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime , 0.0f, 1.0f);

	// ũ���Ŀ� ���� �ݴ����
	Vector pos = m_startPos * m_t + OBJECT->GetPlayer()->Position() * (1 - m_t);
	SetPosition_Creature(pos);

	// �����Ÿ� ������ �� m_t�� 1�ΰ�� Ȥ�� ũ���Ŀ� �浹ó�� �Ǹ� �Ѿ� ����
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
		// ũ���� �浹ü�� �浹�� �ǰ�, z�� �������� ���̰� �¾ƾ� �ϰ�, m_t�� �������� �Ÿ��� �¾ƾ� �ѿ� ���� ������ ���� 
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

// ī�޶� ȸ���� ���� StartPos ������Ʈ. �����δ� �Ѿ��� ������
void Bullet::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection);
	angle += OBJECT->GetDeltaSightAngle();

	// �� p(0,0)�� �������� ������ ���ο� pos�� �÷��̾� ���� p'(MINI_WIDTH * 0.5, MINI_HEIGHT) �������� (*it)�� ��ǥ ����
	Vector pos = MATH->ToDirection(angle) * m_range + OBJECT->GetPlayer()->Position();

	m_startPos = pos;
}