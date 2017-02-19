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
	
	// z좌표 초기화
	m_maxZ = 300;
	m_minZ = m_maxZ;

	m_isDestroyed = false;
}


Creature::~Creature()
{
}

void Creature::Update(float deltaTime)
{
	//cout << m_maxZ << "           " << m_minZ << "           " << Animation()->Current()->GetSprite()->GetHeight()  << "           " << m_t<<endl;	// 콘솔창에서 디버깅용

	// 크리쳐 이동방향벡터 실시간 업데이트
	m_moveDirection = Vector(Position() * -1 + Vector(MINI_WIDTH * 0.5, MINI_HEIGHT)).Normalize();

	// 카메라 회전에 따른 크리쳐 StartPos 업데이트
	StartPosUpdate();

	// 카메라 회전에 따른 크리쳐의 현재 위치를 미니맵 상에서 이동
	Vector pos = m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;
	SetPosition_Creature(pos);

	// m_lifeBar targetValue 업데이트
	m_lifeBar->SetTargetValue(m_currentLife / m_maxLife);
	m_lifeBar->SetCenter(Position() - Vector(0, Animation()->Current()->GetHeight()));

	// m_maxZ 및 m_minZ 업데이트
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
	// 이미지 출력 전 이동에 따른 이미지 스케일 키워주는 부분
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

	// 크리쳐 이동에 관계된 비율 (시작점에서 플레이어까지 가는 거리를 1로 봤을 때, 현재 이동한 거리의 비율)
	m_t = MATH->Clamp(m_t + m_moveSpeed * deltaTime, 0.0f, 1.0f);

	// m_t가 0.9이하면 공격모드로
	if(m_t >= 0.9) m_state = CREATURE_ATTACK;

	// 체력 0이하면 죽음
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
	else if (m_attackCoolTime <= 0.0f) // 공격 쿨타임이 0이하이면 공격 애니메이션 발동 및 벙커 체력에 손실을 입히고, 새로 쿨타임 설정
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
		m_attackCoolTime -= deltaTime;	//	쿨타임 있을 시, 공격 행위를 하지 않고 쿨타임 감소만...
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

// 카메라 회전에 의한 StartPos 업데이트
void Creature::StartPosUpdate()
{
	float angle = MATH->Angle(Vector::Right(), m_moveDirection * -1);
	angle += OBJECT->GetDeltaSightAngle();

	// 점 p(0,0)를 기준으로 구해진 새로운 pos를 플레이어 위지 p'(MINI_WIDTH * 0.5, MINI_HEIGHT) 기준으로 (*it)의 좌표 보정
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