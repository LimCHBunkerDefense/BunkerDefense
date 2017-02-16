#include "Grenade.h"



Grenade::Grenade()
{
}

Grenade::Grenade(OBJ_TAG tag, GRENADE_STATE gre_state) : Object(tag)
{
	CreatureData* pData = CREATURE->GetData(tag);
	m_scale = 1.0f;
	m_state = gre_state;
	m_addHeight = 0.0F;
	m_t = 0.0F;
	m_goal = 1.0F;
	m_moveSpeed = 0.5F;
	m_explodetime = 0.0F;
	
	switch (gre_state) {
	case GRENADE_IDLE:
		m_explodeEnd = 0.9F;
		m_explodeSize = 10.0f;
		break;
	case FLAME_IDLE:
		m_explodeEnd = 3.5F;
		m_explodeSize = 15.0f;
		break;
	case AIRBOMB_IDLE:
		m_explodeEnd = 10.0F;
		m_explodeSize = 20.0f;
		break;
	default:
		m_explodeEnd = 0.0F;
		break;
	}
	
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
}


Grenade::~Grenade()
{
}

//�ε����� �����ǰ� �ϱ� ���� BOOL �Լ� �߰�
BOOL Grenade::UpdateBool(float deltaTime) {
	
	//������ ���� ���ϰ� �ϱ� ���� �߰�
	if (m_t <= m_goal / 2)	m_addHeight -= 30;
	else if (m_t <= m_goal) {
		m_addHeight += 30;
		if (m_addHeight > 0) {
			m_addHeight = 0;
		}
	}
	
	// �÷��̾��� ī�޶� ȸ���� ���� StartPos ������Ʈ
	//StartPosUpdate();

	BOOL result=false;
	m_moveDirection = Vector(m_startPos * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	// �÷��̾��� ī�޶� ȸ���� ���� StartPos ������Ʈ
	StartPosUpdate();


	// ũ���Ŀ� ���� �ݴ����
	Vector pos = GetNowPos();
	SetPosition_Creature(pos, pos * 5);

	//cout << Position().x << "   " << Position().y << "       " << m_t << endl;

	switch (m_state)
	{
		case GRENADE_IDLE:		IdleState(deltaTime); break;
		case GRENADE_EXPLODE:	result = HitState(deltaTime); break;
		case FLAME_IDLE:		IdleState(deltaTime); break;
		case FLAME_EXPLODE:		result = HitState(deltaTime); break;
		case AIRBOMB_IDLE:		IdleState(deltaTime); break;
		case AIRBOMB_EXPLODE:	result = HitState(deltaTime); break;
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
	

	Animation()->Play(m_state);
	//if (m_state == AIRBOMB_IDLE) m_goal = 0.9f;
	if (m_t >= m_goal) m_state = GetStateExplode(m_state);
	
}

GRENADE_STATE Grenade::GetStateExplode(GRENADE_STATE gre_state) {
	switch (gre_state) {
	case GRENADE_IDLE:
		return GRENADE_EXPLODE;
		break;
	case FLAME_IDLE:
		return FLAME_EXPLODE;
		break;
	case AIRBOMB_IDLE:
		return AIRBOMB_EXPLODE;
		break;
	default:
		return GRENADE_NONE;
		break;
	}
}

void Grenade::Collided()
{
	list<Object*> creatureList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, creatureList) {
		if (MATH->Distance(Position(), (*it)->GetNowPos())<= m_explodeSize){
			OBJECT->DestroyCreature((*it));
		}
	}
}
BOOL Grenade::HitState(float deltaTime) {
	m_explodetime = MATH->Clamp(m_explodetime + m_moveSpeed * deltaTime, 0.0f, 100.0f);
	Animation()->Play(m_state);
	Collided();
	if (m_explodetime <= m_explodeEnd)	return false;
	else								return true;
}

void Grenade::Draw(Camera* pCamera)
{
	SetCollider(Collider().size * ((1 - m_t) *1.0f) / m_scale, Collider().anchor);
	switch (m_state)
	{
		case GRENADE_IDLE:		SetScale((1 - m_t) *0.2f); break;
		case GRENADE_EXPLODE:	SetScale((1 - m_t) *6.0f); break;
		case FLAME_IDLE:		SetScale((1 - m_t) *0.2f); break;
		case FLAME_EXPLODE:		SetScale((1 - m_t) *6.0f); break;
		case AIRBOMB_IDLE:		SetScale((1 - m_t) *2.0f); break;
		case AIRBOMB_EXPLODE:	SetScale(3.0f); break;
	}

	//Vector startPos = m_startPos * m_goal + OBJECT->GetPlayer()->Position() * (1 - m_goal);

	if (m_state == AIRBOMB_IDLE) {
		pCamera->Draw3D(Animation()->Current()->GetSprite(), m_startPos, 1 - m_t, OBJECT->GetSightHeight()+150, m_state);
	}
	else if (m_state == AIRBOMB_EXPLODE) {
		//pCamera->Draw3D(Animation()->Current()->GetSprite(), m_startPos, 1 - m_t, OBJECT->GetSightHeight(), m_state, m_addHeight);
		pCamera->Draw3D(Animation()->Current()->GetSprite(), m_startPos, 0.5,400, m_state);
	}
	else {
		pCamera->Draw3D(Animation()->Current()->GetSprite(), m_startPos, 1 - m_t, OBJECT->GetSightHeight(), m_state, m_addHeight);
	}
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