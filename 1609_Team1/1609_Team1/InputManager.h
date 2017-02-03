#pragma once
#include "Singleton.h"
#include "Common.h"
#include <Windows.h>

#define INPUT InputManager::Instance()

class InputManager : public Singleton<InputManager>
{
	HWND m_hWnd;
	KEY_STATE m_keyStates[KEY_COUNT];
	MOUSE_STATE m_mouseStates[MOUSE_COUNT];

	POINT m_mousePrevPos;
	POINT m_mouseCurrentPos;
	POINT m_mouseDeltaPos;

	void UpdateKeyState();
	void UpdateMouseState();

public:
	InputManager();
	~InputManager();

	void Init(HWND hWnd);
	void Release();
	void Update();

	KEY_STATE GetKeyState(int key) { return m_keyStates[key]; }
	MOUSE_STATE GetMouseState(MOUSE_BUTTON btn) { return m_mouseStates[btn]; }

	POINT GetMousePos() { return m_mouseCurrentPos; }
	POINT GetMouseDelta() { return m_mouseDeltaPos; }

	bool IsKeyDown(int key) { return GetKeyState(key) == KEY_DOWN; }
	bool IsKeyUp(int key) { return GetKeyState(key) == KEY_UP; }
	bool IsKeyPress(int key) { return GetKeyState(key) == KEY_PRESS; }

	bool IsMouseDown(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_DOWN; }
	bool IsMouseUp(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_UP; }
	bool IsMousePress(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_PRESS; }
	bool IsMouseDrag(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_DRAG; }
};