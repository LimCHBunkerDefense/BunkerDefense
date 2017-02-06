#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	m_frameTime = 1.0f / (float)FPS;
	m_currentTime = (float)timeGetTime() * 0.001f;
	m_prevTime = (float)timeGetTime() * 0.001f;

	WINDOW->RegisterData(TEXT("Main"), CS_HREDRAW | CS_VREDRAW, RGB(255, 255, 255), WndProc);
	WINDOW->Create(WND_MAIN, TEXT("Main"), TEXT("MainWindow"), 0, 0, VIEW_WIDTH, VIEW_HEIGHT);

	RENDER->Init(WINDOW->GetHandle(WND_MAIN));
	INPUT->Init(WINDOW->GetHandle(WND_MAIN));

	SCENE->Register(SCENE_PLAY, new PlayScene());
	SCENE->Register(SCENE_SHOP, new ShopScene()); // *������ �߰�
	SCENE->ChangeScene(SCENE_PLAY); // ���� Ȯ�������ؿ� ����
}

void GameManager::Release()
{
	INPUT->Release();
	RENDER->Release();
	WINDOW->Destroy(WND_MAIN);
}

void GameManager::Update()
{
	m_currentTime = (float)timeGetTime() * 0.001f;
	float deltaTime = m_currentTime - m_prevTime;	// ���� �� ������ �ð�

	if (deltaTime >= m_frameTime)
	{
		m_prevTime = m_currentTime;

		INPUT->Update();
		SCENE->Update(deltaTime);

		InvalidateRect(WINDOW->GetHandle(WND_MAIN), NULL, false);
	}
}

void GameManager::Render(HDC hdc)
{
	//ShowMouseState(); // �ʿ��� ����

	SCENE->Draw();

	RENDER->Render(hdc);
}

void GameManager::ShowMouseState()
{
	TCHAR text[100] = {};

	POINT mousePos = INPUT->GetMousePos();
	wsprintf(text, TEXT("Mouse(%d, %d)"), mousePos.x, mousePos.y);
	RENDER->DrawT(text, 0, 0);

	switch (INPUT->GetMouseState(MOUSE_LEFT))
	{
	case MOUSE_NONE: RENDER->DrawT(TEXT("Mouse(None)"), 0, 20); break;
	case MOUSE_DOWN: RENDER->DrawT(TEXT("Mouse(Down)"), 0, 20); break;
	case MOUSE_UP: RENDER->DrawT(TEXT("Mouse(Up)"), 0, 20); break;
	case MOUSE_PRESS: RENDER->DrawT(TEXT("Mouse(Press)"), 0, 20); break;
	case MOUSE_DRAG: RENDER->DrawT(TEXT("Mouse(Drag)"), 0, 20); break;
	}
}

LRESULT CALLBACK GameManager::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		GAME->Render(hdc);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}