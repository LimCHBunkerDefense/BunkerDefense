#pragma once
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "ProgressBar.h"
#include "BulletBar.h"
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
	Sprite* m_ico_shotGun;
	Sprite* m_ico_machineGun;
	Sprite* m_ico_laserGun;
	Sprite* m_ico_grenade;
	Sprite* m_ico_plane;
	Sprite* m_ico_napalm;
	Sprite* m_ico_fix;

	//ui
	Sprite* m_stageUI;	
	Sprite* m_BunkerUI;
	Sprite* m_ItemBarUI;
	Sprite* m_ScoreUI;
	Sprite* m_MoneyUI;
	Sprite* m_ProgressBarIconUI;
	Sprite* m_BulletBarIconUI;


	Camera* pMainCamera;
	Camera* pMinimapCamera;
	Camera* pUICamera;
	Vector m_MainCameraPos;
	Vector m_swayPos;

	UIProgressBar* m_bunkerLife;
	UIBulletBar* m_bulletGage;


	// 숫자 스프라이트 생성해놓기
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

	// 크리쳐 공격 연출을 위한 도구(색 저장용)
	ColorF m_attackedColor;

	
	// 크리쳐 생성 y좌표(높이 h)
	//float m_heightOfCreature;

	// 화면 출력을 위한 시야의 각도
	float m_angleToSee;

	// 크리쳐 생성을 위한 게임 시간
	float m_gameTime;
	
	// 생성된 크리쳐들 수
	int m_createdLavaCount;
	int m_createdEntCount;
	int m_createdDarkpriestCount;


	
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
	
	// Creature에서 공격시 m_attackedColor 투명도 조정을 위한 함수
	void SetAttackedColor() { m_attackedColor.a = 0.5; }

	// 공격 당하고 있음을 연출해주는 함수
	void SwayScreen(float deltaTime);

	// 플레이어의 돈과 점수 출력해주는 함수
	void ShowMoney(Camera* pCamera);
	void ShowScore(Camera* pCamera);
	void ShowBullet(Camera* pCamera, INT bullet, Vector startPos);

	// 숫자를 스프라이트로 출력해주는 함수
	void DrawNum(Camera* pCamera, int num, Vector leftTop);
};