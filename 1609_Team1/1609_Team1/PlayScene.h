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
	Vector m_posBg;

	Sprite* m_pAim;
	Sprite* m_pMinimap;
	Sprite* m_pRadar;

	
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
	void SetPosBg(Vector pos) { m_posBg = pos; }
	Vector GetPosBg() { return m_posBg; }
};