#pragma once
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "CreatureDB.h"
#include "Common.h"
#include "Math.h"

class PlayScene : public IScene
{
	Sprite* m_pBg;

	
	// ũ���� ���� y��ǥ(���� h)
	float m_heightOfCreature;

	// ȭ�� ����� ���� �þ��� ����
	float m_angleToSee;

	// ũ���� ������ ���� ���� �ð�
	float m_gameTime;
	
	// ũ���� �� ������ ��
	int m_createdCretureCount;
	
public:
	PlayScene();
	~PlayScene();

	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void SetCreature(float deltaTime);
};