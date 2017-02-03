#include "WindowManager.h"



WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}

void WindowManager::RegisterData(TCHAR* dataName, UINT style, COLORREF bgColor, WNDPROC wndProc)
{
	WNDCLASS* pWndClass = new WNDCLASS;
	pWndClass->cbClsExtra = 0;		// 특수 목적을 위한 예비 공간
	pWndClass->cbWndExtra = 0;		// 특수 목적을 위한 예비 공간
	pWndClass->hbrBackground = CreateSolidBrush(bgColor);	// 백그라운드 브러시 설정
	pWndClass->hCursor = LoadCursor(NULL, IDC_ARROW);		// 커서 설정
	pWndClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 아이콘 설정
	pWndClass->hInstance = g_hInst;						// 인스턴스 설정
	pWndClass->lpfnWndProc = wndProc;						// 메시지 처리 함수 설정
	pWndClass->lpszClassName = dataName;					// 윈도우 이름 설정
	pWndClass->lpszMenuName = NULL;						// 메뉴 설정 (메뉴가 없는 윈도우는 NULL)
	pWndClass->style = style;			// 윈도우의 가로세로 크기가 변할시에 다시 그린다.

	RegisterClass(pWndClass);
}

Window* WindowManager::Get(int windowID)
{
	if (m_windows.find(windowID) != m_windows.end())
	{
		return m_windows[windowID];
	}
	return NULL;
}

HWND WindowManager::GetHandle(int windowID)
{
	Window* pWindow = Get(windowID);
	if (pWindow != NULL)
	{
		return pWindow->handle;
	}
	return NULL;
}

void WindowManager::Create(int windowID, TCHAR* dataName, TCHAR* title, int x, int y, int width, int height)
{
	DWORD style = WS_CAPTION | WS_SYSMENU;
	HWND hWnd = CreateWindow(dataName, title, style, x, y, width, height, NULL, NULL, g_hInst, NULL);
	ShowWindow(hWnd, SW_SHOW);

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, style, false);
	MoveWindow(hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);

	m_windows[windowID] = new Window(hWnd, x, y, width, height);
}

void WindowManager::Destroy(int windowID)
{
	Window* pWindow = Get(windowID);
	if (pWindow != NULL)
	{
		m_windows.erase(windowID);
		delete pWindow;
	}
}

LRESULT WindowManager::Send(int windowID, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* pWindow = Get(windowID);
	if (pWindow != NULL)
	{
		return SendMessage(pWindow->handle, msg, wParam, lParam);
	}
	return -1;
}

