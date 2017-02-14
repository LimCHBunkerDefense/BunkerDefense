#pragma once
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "ProgressBar.h"
#include "CreatureDB.h"
#include "Common.h"
#include "Math.h"

class PlayScene : public IScene
{
	Sprite* m_pBg;

	Sprite* m_pAim;
	Sprite* m_pMinimap;
	Sprite* m_pRadar;

	//ico
	Sprite* m_ico_pistol;
	Sprite* m_ico_laser;
	Sprite* m_ico_machine;

	//ui
	Sprite* m_stageUI;
	Sprite* m_BunkerUI;
	Sprite* m_ItemBarUI;
	Sprite* m_ScoreUI;
	Sprite* m_MoneyUI;


	Camera* pMainCamera;
	Camera* pMinimapCamera;
	Camera* pUICamera;

	UIProgressBar* m_bunkerLife;

	// ũ���� ���� ������ ���� ����(�� �����)
	ColorF m_attackedColor;

	
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

	void DrawBG();
	void SetCreature(float deltaTime);
	void ChangeIcon();
	
	// m_attackedColor ���� �����Ͽ� ���ݴ��� ����
	void SetAttackedColor() { m_attackedColor.a = 20; }
};