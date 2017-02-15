#pragma once
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "ProgressBar.h"
#include "CreatureDB.h"
#include "Common.h"
#include "Math.h"
#include "UIProgressBar.h"

class PlayScene : public IScene
{
	UIProgressBar* m_pBar;//ü�¹�
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
	Vector m_MainCameraPos;
	Vector m_swayPos;

	UIProgressBar* m_bunkerLife;

	// ���� ��������Ʈ �����س���
	Sprite* m_num1;
	Sprite* m_num2;
	Sprite* m_num3;
	Sprite* m_num4;
	Sprite* m_num5;
	Sprite* m_num6;
	Sprite* m_num7; 
	Sprite* m_num8;
	Sprite* m_num9;
	Sprite* m_num0;

	// ũ���� ���� ������ ���� ����(�� �����)
	ColorF m_attackedColor;

	
	// ũ���� ���� y��ǥ(���� h)
	//float m_heightOfCreature;

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
	
	// Creature���� ���ݽ� m_attackedColor ���� ������ ���� �Լ�
	void SetAttackedColor() { m_attackedColor.a = 0.5; }

	// ���� ���ϰ� ������ �������ִ� �Լ�
	void SwayScreen(float deltaTime);

	// �÷��̾��� ���� ���� ������ִ� �Լ�
	void ShowMoney(Camera* pCamera);
	void ShowScore(Camera* pCamera);

	// ���ڸ� ��������Ʈ�� ������ִ� �Լ�
	void DrawNum(Camera* pCamera, int num, Vector leftTop);
};