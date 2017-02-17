#pragma once
#pragma comment(lib, "winmm.lib")
#include "Singleton.h"
#include "WindowManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Common.h"
#include "PlayScene.h"
#include "ShopScene.h"

#define GAME GameManager::Instance()


class GameManager : public Singleton<GameManager>
{
	float m_frameTime;			// 한 프레임당 시간
	int m_currentTime;		// 현재 프레임의 시간
	int m_prevTime;			// 이전 프레임의 시간

public:
	GameManager();
	~GameManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void ShowMouseState();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};