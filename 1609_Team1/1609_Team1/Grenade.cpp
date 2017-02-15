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
	m_addHeight = 0.0F;
	m_t = 0.0F;
	m_goal = 1.0F;
	m_moveSpeed = 0.5F;
	m_explodetime = 0.0F;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Grenade::~Grenade()
{
}

//�ε����� �����ǰ� �ϱ� ���� BOOL �Լ� �߰�
BOOL Grenade::UpdateBool(float deltaTime) {
	//������ ���� ���ϰ� �ϱ� ���� �߰�
	if		(m_t <= m_goal/2)	m_addHeight -= 30;
	else if (m_t<=m_goal)		m_addHeight += 30;

	// �÷��̾��� ī�޶� ȸ���� ���� StartPos ������Ʈ
	StartPosUpdate();

	BOOL result=false;
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	// ũ���Ŀ� ���� �ݴ����
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
	
	// �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);
	

	Animation()->Play(GRENADE_IDLE);
	if (m_t >= m_goal) m_state = GRENADE_EXPLODE;
	
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
	Collided();
	if (m_explodetime <= 0.9F)	return false;
	else						return true;
}

void Grenade::Draw(Camera* pCamera)
{
	SetCollider(Collider().size * ((1 - m_t) *1.0f) / m_scale, Collider().anchor);
	switch (m_state)
	{
		case GRENADE_IDLE:		SetScale((1 - m_t) *0.2f); break;
		case GRENADE_EXPLODE:	SetScale((1 - m_t) *6.0f); break;
	}
//	SetScale((m_goal - m_t) *1.0f + 0.2f) ;
	Vector startPos = m_startPos * m_goal + OBJECT->GetPlayer()->Position() * (1 - m_goal);
	//Vector gap = Vector(VIEW_WIDTH, VIEW_HEIGHT) - OBJECT->GetAimPos();
	//pCamera->Draw3D(Animation()->Current()->GetSprite(), Vector(m_startPos.x, m_startPos.y), (1 - m_t), OBJECT->GetSightHeight(), m_state);
	//pCamera->Draw3D(Animation()->Current()->GetSprite(), startPos, (m_goal-m_t)/m_goal, OBJECT->GetSightHeight(), m_state);
	pCamera->Draw3D(Animation()->Current()->GetSprite(), m_startPos, 1-m_t, OBJECT->GetSightHeight(), m_state, m_addHeight);
}

// ī�޶� ȸ���� ���� StartPos ������Ʈ
void Grenade::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection * -1);
	angle += OBJECT->GetDeltaSightAngle();

	// �� p(0,0)�� �������� ������ ���ο� pos�� �÷��̾� ���� p'(MINI_WIDTH * 0.5, MINI_HEIGHT) �������� (*it)�� ��ǥ ����
	Vector pos = MATH->ToDirection(angle) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();

	m_startPos = pos;
}