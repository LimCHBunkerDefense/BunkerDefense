#include "Creature.h"



Creature::Creature()
{
	m_state = CREATURE_RUN;
	m_dir = DIRECTION_CENTER;
}

Creature::Creature(OBJ_TAG tag) : Object(tag)
{
	CreatureData* pData = CREATURE->GetData(tag);
	m_state = CREATURE_RUN;
	m_dir = DIRECTION_CENTER;

	m_t = 0.0f;
	m_attack = pData->attack;
	m_defense = pData->defense;
	m_name = pData->name;
	m_attackSpeed = pData->attackSpeed;
	m_attackCoolTime = 0;
	m_moveSpeed = pData->moveSpeed;
	m_maxLife = pData->life;
	m_currentLife = m_maxLife;
	m_money = pData->money;
	m_score = pData->score;

	m_lifeBar = new UIProgressBar(Vector(0, 0), Vector(400, 20), ColorF::Blue, ColorF::LightSlateGray);
	m_lifeBar->SetMinMaxColor(ColorF::DarkRed, ColorF::DarkOliveGreen);

	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();
	
	// z��ǥ �ʱ�ȭ
	m_maxZ = 300;
	m_minZ = m_maxZ;

	m_isDestroyed = false;
}


Creature::~Creature()
{
}

void Creature::Update(float deltaTime)
{
	//cout << m_maxZ << "           " << m_minZ << "           " << Animation()->Current()->GetSprite()->GetHeight()  << "           " << m_t<<endl;	// �ܼ�â���� ������

	// ũ���� �̵����⺤�� �ǽð� ������Ʈ
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	// ī�޶� ȸ���� ���� ũ���� StartPos ������Ʈ
	StartPosUpdate();

	// ī�޶� ȸ���� ���� ũ������ ���� ��ġ�� �̴ϸ� �󿡼� �̵�
	Vector pos = m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;
	SetPosition_Creature(pos);

	// m_lifeBar targetValue ������Ʈ
	m_lifeBar->SetTargetValue(m_currentLife / m_maxLife);
	m_lifeBar->SetCenter(Position() - Vector(0, Animation()->Current()->GetHeight()));

	// m_maxZ �� m_minZ ������Ʈ
	ZUpdate();

	switch (m_state)
	{
	case CREATURE_IDLE: IdleState(deltaTime); break;
	case CREATURE_ATTACK: AttackState(deltaTime); break;
	case CREATURE_RUN: RunState(deltaTime); break;
	case CREATURE_DEAD: DeadState(deltaTime); break;

	}

	Animation()->Update(deltaTime);
}

void Creature::Draw(Camera* pCamera)
{
	// �̹��� ��� �� �̵��� ���� �̹��� ������ Ű���ִ� �κ�
	SetScale(OriginScale() * m_t * m_t * 3.0f);
	m_scale = OriginScale() * m_t * m_t * 3.0f;



	pCamera->Draw3D(Animation()->Current()->GetSprite(), m_startPos, m_t, OBJECT->GetSightHeight(), m_state);
}

void Creature::IdleState(float deltaTime)
{
	Animation()->Play(CREATURE_IDLE);
}

void Creature::RunState(float deltaTime)
{
	Animation()->Play(CREATURE_RUN);

	// ũ���� �̵��� ����� ���� (���������� �÷��̾���� ���� �Ÿ��� 1�� ���� ��, ���� �̵��� �Ÿ��� ����)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);

	// m_t�� 0.9���ϸ� ���ݸ���
	if(m_t >= 0.9) m_state = CREATURE_ATTACK;

	// ü�� 0���ϸ� ����
	if (m_currentLife <= 0.0f)
	{
		Animation()->Play(CREATURE_DEAD);
		OBJECT->GetPlayer()->AddMoney(m_money);
		OBJECT->GetPlayer()->AddScore(m_score);
		m_state = CREATURE_DEAD;
	}


}

void Creature::AttackState(float deltaTime)
{
	if (m_currentLife <= 0.0f)
	{
		Animation()->Play(CREATURE_DEAD);
		OBJECT->GetPlayer()->AddMoney(m_money);
		OBJECT->GetPlayer()->AddScore(m_score);
		m_state = CREATURE_DEAD;
	}
	else if (m_attackCoolTime <= 0.0f) // ���� ��Ÿ���� 0�����̸� ���� �ִϸ��̼� �ߵ� �� ��Ŀ ü�¿� �ս��� ������, ���� ��Ÿ�� ����
	{
		Animation()->Play(CREATURE_ATTACK);
		float addLife = OBJECT->GetBunker()->GetDefense() - m_attack;
		OBJECT->GetBunker()->AddCurrentLife(addLife);
		m_attackCoolTime = m_attackSpeed;
		SCENE->GetScene(SCENE_PLAY)->SetAttackedColor();
		switch (Tag())
		{
		case OBJ_ENT:
			if(Animation()->Current()->GetCurrentIndex() == 7) SCENE->GetScene(SCENE_PLAY)->SetAttackedColor();
			break;
		}
	}

	else
	{
		m_attackCoolTime -= deltaTime;	//	��Ÿ�� ���� ��, ���� ������ ���� �ʰ� ��Ÿ�� ���Ҹ�...
	}
	
}

void Creature::DeadState(float deltaTime)
{
	switch (Tag())
	{
	case OBJ_LAVA:
		if (Animation()->Current()->GetCurrentIndex() == 12) m_isDestroyed = true;
		break;
	case OBJ_ENT:
		if (Animation()->Current()->GetCurrentIndex() == 6) m_isDestroyed = true;
		break;
	case OBJ_DARKPRIEST:
		if (Animation()->Current()->GetCurrentIndex() == 22) m_isDestroyed = true;
		break;
	}
	
}

// ī�޶� ȸ���� ���� StartPos ������Ʈ
void Creature::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection * -1);
	angle += OBJECT->GetDeltaSightAngle();

	// �� p(0,0)�� �������� ������ ���ο� pos�� �÷��̾� ���� p'(MINI_WIDTH * 0.5, MINI_HEIGHT) �������� (*it)�� ��ǥ ����
	Vector pos = MATH->ToDirection(angle) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();

	m_startPos = pos;
}

void Creature::ZUpdate()
{
	m_maxZ = 300 + 350 * m_t;
	
	float gap;
	switch (Tag())
	{
	case OBJ_LAVA:
		gap = 0.5;
		break;
	case OBJ_ENT:
		gap = 0.55;
		break;
	case OBJ_DARKPRIEST:
		gap = 0.6;
		break;
	}
	m_minZ = m_maxZ - (Animation()->Current()->GetSprite()->GetHeight() * gap);

}