#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::UpdateKeyState()
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		bool isPressed = GetAsyncKeyState(i) & 0x8000;
		if (isPressed)
		{
			switch (m_keyStates[i])
			{
			case KEY_NONE: m_keyStates[i] = KEY_DOWN; break;
			case KEY_DOWN: m_keyStates[i] = KEY_PRESS; break;
			case KEY_UP: m_keyStates[i] = KEY_DOWN; break;
			}
		}
		else
		{
			switch (m_keyStates[i])
			{
			case KEY_DOWN: m_keyStates[i] = KEY_UP; break;
			case KEY_PRESS: m_keyStates[i] = KEY_UP; break;
			case KEY_UP: m_keyStates[i] = KEY_NONE; break;
			}
		}
	}
}

void InputManager::UpdateMouseState()
{
	m_mousePrevPos = m_mouseCurrentPos;
	GetCursorPos(&m_mouseCurrentPos);		// 스크린 좌표
	ScreenToClient(m_hWnd, &m_mouseCurrentPos);	// 스크린 -> 작업영역 좌표
	m_mouseDeltaPos.x = m_mouseCurrentPos.x - m_mousePrevPos.x;
	m_mouseDeltaPos.y = m_mouseCurrentPos.y - m_mousePrevPos.y;

	for (int i = 0; i < MOUSE_COUNT; i++)
	{
		int vKey = 0;
		switch (i)
		{
		case MOUSE_LEFT: vKey = VK_LBUTTON; break;
		case MOUSE_CENTER: vKey = VK_MBUTTON; break;
		case MOUSE_RIGHT: vKey = VK_RBUTTON; break;
		}

		bool isPressed = GetAsyncKeyState(vKey) & 0x8000;

		if (isPressed)
		{
			switch (m_mouseStates[i])
			{
			case MOUSE_NONE: m_mouseStates[i] = MOUSE_DOWN; break;
			case MOUSE_DOWN:
				if (m_mouseDeltaPos.x == 0 && m_mouseDeltaPos.y == 0)
				{
					m_mouseStates[i] = MOUSE_PRESS;
				}
				else
				{
					m_mouseStates[i] = MOUSE_DRAG;
				}
				break;
			case MOUSE_PRESS:
				if (m_mouseDeltaPos.x != 0 || m_mouseDeltaPos.y != 0)
				{
					m_mouseStates[i] = MOUSE_DRAG;
				}
				break;
			case MOUSE_DRAG:
				if (m_mouseDeltaPos.x == 0 && m_mouseDeltaPos.y == 0)
				{
					m_mouseStates[i] = MOUSE_PRESS;
				}
				break;
			case MOUSE_UP: m_mouseStates[i] = MOUSE_DOWN; break;
			}
		}
		else
		{
			switch (m_mouseStates[i])
			{
			case MOUSE_DOWN: m_mouseStates[i] = MOUSE_UP; break;
			case MOUSE_PRESS: m_mouseStates[i] = MOUSE_UP; break;
			case MOUSE_DRAG: m_mouseStates[i] = MOUSE_UP; break;
			case MOUSE_UP: m_mouseStates[i] = MOUSE_NONE; break;
			}
		}
	}
}


void InputManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	GetCursorPos(&m_mousePrevPos);
	ScreenToClient(hWnd, &m_mousePrevPos);
	m_mouseCurrentPos = m_mousePrevPos;

	for (int i = 0; i < KEY_COUNT; i++)
	{
		m_keyStates[i] = KEY_NONE;
	}

	for (int i = 0; i < MOUSE_COUNT; i++)
	{
		m_mouseStates[i] = MOUSE_NONE;
	}
}

void InputManager::Release()
{

}

void InputManager::Update()
{
	UpdateKeyState();
	UpdateMouseState();
}