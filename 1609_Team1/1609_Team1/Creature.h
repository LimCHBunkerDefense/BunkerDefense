#pragma once
#include "ObjectManager.h"
#include "SceneManager.h"
#include "CreatureDB.h"
#include "ProgressBar.h"

class Creature :
	public Object
{
	float m_attack;
	float m_defense;
	wstring m_name;
	Sprite* m_pSprite;
	float m_attackCoolTime;
	float m_attackSpeed;
	float m_moveSpeed;
	float m_maxLife;
	float m_currentLife;
	int m_money;
	int m_score;
	UIProgressBar* m_lifeBar;

	// 3D화면에서 총알에 적용된 z값과 비교하여 충돌처리를 하기 위한 z의 최소값과 최대값
	float m_minZ;
	float m_maxZ;		// 크리쳐 z의 최하점(x,y좌표 반대이므로)으로써, 이 점을 움직이고 minZ를 보정하도록 함

	Vector m_startPos;
	float m_scale;
	float m_t;
	CREATURE_STATE m_state;
	DIRECTION_TAG m_dir;
	Vector m_moveDirection;

	bool m_isDestroyed;	//	 죽는 애니메이션 끝나면 삭제될 수 있도록 나타내는 값

public:
	Creature();
	Creature(OBJ_TAG tag);
	~Creature();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void IdleState(float deltaTime);
	void RunState(float deltaTime);
	void AttackState(float deltaTime);
	void DeadState(float deltaTime);

	void SetMoveDirection(Vector vector) { m_moveDirection = vector; }
	Vector GetMoveDirection() { return m_moveDirection; }
	Vector GetNowPos(){return  m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;}

	void StartPosUpdate();
	void ZUpdate();
	void SetStartPos(Vector pos) { m_startPos = pos; }
	Vector GetStartPos() { return m_startPos; }
	float GetMT() { return m_t; }
	float GetMaxZ() { return m_maxZ; }
	float GetMinZ() { return m_minZ; }
	void AddCurrentLife(float addLife) { m_currentLife = MATH->Clamp(m_currentLife + addLife, 0.0f, m_maxLife); }
	float GetCurrentLife() { return m_currentLife; }
	bool IsDestroyed() { return m_isDestroyed; }

	int GetScore() { return m_score; }
	int GetMoney() { return m_money; }

	//콜라이더 각도 구해서 리턴
	float GetCollideAngle() {
		Vector pos = m_startPos * (1 - m_t) + OBJECT->GetPlayer()->Position() * m_t;
		Vector box = (Collider().size * (m_t *2.0f))/2;
		Vector v_center = Position() - OBJECT->GetPlayer()->Position();
		Vector v_side = box + pos - OBJECT->GetPlayer()->Position();
		float a = MATH->CosAngle(v_center, v_side) * 2;
		return a;
	}

};

