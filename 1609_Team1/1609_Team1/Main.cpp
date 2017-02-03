#include "GameManager.h"

HINSTANCE g_hInst;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	g_hInst = hInstance;

	GAME->Init();

	// 메시지 루프
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);		// 메시지 번역
			DispatchMessage(&msg);		// 메시지 처리 함수 호출
		}

		GAME->Update();
	}

	GAME->Release();

	return (int)msg.wParam;
}