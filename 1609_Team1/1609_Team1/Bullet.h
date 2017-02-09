#pragma once
#include "ObjectManager.h"
#include "CreatureDB.h"

class Bullet :
	public Object
{
	BULLET_STATE m_state;
	Sprite* m_pSprite;
	float m_moveSpeed;

	float m_scale;
	Vector m_moveDirection;
	DIRECTION_TAG m_dir;

public:
	Bullet();
	Bullet(OBJ_TAG tag);
	~Bullet();

	void Update(float deltaTime);
	void Draw(Camera* pCamera);

	void SetMoveDirection(Vector vector) { m_moveDirection = vector; }
	Vector GetMoveDirection() { return m_moveDirection; }

};

