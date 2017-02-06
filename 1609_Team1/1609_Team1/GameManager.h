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
	float m_frameTime;			// �� �����Ӵ� �ð�
	float m_currentTime;		// ���� �������� �ð�
	float m_prevTime;			// ���� �������� �ð�

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