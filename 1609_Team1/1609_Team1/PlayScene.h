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

	// 크리쳐 공격 연출을 위한 도구(색 저장용)
	ColorF m_attackedColor;

	
	// 크리쳐 생성 y좌표(높이 h)
	float m_heightOfCreature;

	// 화면 출력을 위한 시야의 각도
	float m_angleToSee;

	// 크리쳐 생성을 위한 게임 시간
	float m_gameTime;
	
	// 크리쳐 총 생성된 수
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
	
	// m_attackedColor 투명도 조정하여 공격당함 연출
	void SetAttackedColor() { m_attackedColor.a = 20; }
};