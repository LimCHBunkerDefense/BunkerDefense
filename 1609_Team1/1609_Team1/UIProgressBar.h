#pragma once
#include "RenderManager.h"
#include "InputManager.h"
#include "Common.h"

enum PROGRESS_STATE
{
	PROGRESS_STATE_NONE,
	PROGRESS_STATE_CHANGE, // 값이 변해가고 있는 상태
	PROGRESS_STATE_DRAG,
};

class UIProgressBar
{
	Box2 m_bar;     // 내부 Bar
	Box2 m_frame;    // 겉의 Bar

	ColorF m_colorMin;   // 가장 작을 때의 칼라
	ColorF m_colorMax;   // 가장 클 때의 칼라
	ColorF m_colorBar;   // 내부 Box의 칼라
	ColorF m_colorFrame;  // frame 칼라
	ColorF m_colorBg;   // 내부 칼라

	PROGRESS_STATE m_state;
	float m_value;
	float m_targetValue;  // 목표 값

	Vector m_originSize;  // 기본 크기
	Vector m_originLeftTop;

public:
	UIProgressBar(Vector center, Vector size, ColorF barColor, ColorF frameColor) :
		m_bar(center, size * 0.99),
		m_frame(center, size),
		m_colorMin(barColor),
		m_colorMax(barColor),
		m_colorBar(barColor),
		m_colorFrame(frameColor),
		m_colorBg(ColorF::Black)
	{
		m_state = PROGRESS_STATE_NONE;
		m_originSize = m_bar.size;
		m_originLeftTop = m_bar.LeftTop();
		SetValue(0.0f);           // 이 비율을 통해 바 크기를 조절
		SetTargetValue(1.0F);
	}

	void SetMinMaxColor(ColorF minColor, ColorF maxColor)
	{
		m_colorMin = minColor;
		m_colorMax = maxColor;
	}

	void SetValue(float value)
	{
		m_value = MATH->Clamp(value, 0.0f, 1.0f);
		m_bar.size.x = MATH->Lerp(0, m_originSize.x, value);
		m_bar.SetLeftTop(m_originLeftTop);
		m_colorBar.r = MATH->Lerp(m_colorMin.r, m_colorMax.r, m_value);
		m_colorBar.g = MATH->Lerp(m_colorMin.g, m_colorMax.g, m_value);
		m_colorBar.b = MATH->Lerp(m_colorMin.b, m_colorMax.b, m_value);
		m_colorBar.a = MATH->Lerp(m_colorMin.a, m_colorMax.a, m_value);
	}

	void SetTargetValue(float value)
	{
		m_targetValue = MATH->Clamp(value, 0.0f, 1.0f);
	}

	void Update(float deltaTime)
	{
		//Vector mousePos = INPUT->GetMousePos();

		switch (m_state)
		{
		case PROGRESS_STATE_NONE:
			/*if (INPUT->IsMouseDown(MOUSE_LEFT))
			{
				if (MATH->IsCollided(mousePos, m_frame))
				{
					m_state = PROGRESS_STATE_DRAG;
				}
			}*/
			if (m_value != m_targetValue)
			{
				m_state = PROGRESS_STATE_CHANGE;
			}
			break;


		case PROGRESS_STATE_CHANGE:
			SetValue(MATH->MoveForward(m_value, m_targetValue, deltaTime));
			if (m_value == m_targetValue) m_state = PROGRESS_STATE_NONE;
			break;

		case PROGRESS_STATE_DRAG:
			/*SetTargetValue((mousePos.x - m_originLeftTop.x) / m_originSize.x);
			SetValue(MATH->MoveForward(m_value, m_targetValue, deltaTime));        // 클릭시 서서히 바꿔주는것 
																				   //SetValue(m_targetValue);              // 바로바로 클릭시 바꿔주는것
			if (INPUT->IsMouseUp(MOUSE_LEFT)) m_state = PROGRESS_STATE_NONE;*/
			break;
		}
	}

	void Render()
	{
		RENDER->FillRect(m_frame.center, m_frame.size, m_colorBg);
		RENDER->FillRect(m_bar.center, m_bar.size, m_colorBar);
		RENDER->DrawRect(m_bar.center, m_bar.size, ColorF(1, 1, 1, 0.3f), 3);
		RENDER->DrawRect(m_frame.center, m_frame.size, m_colorFrame, 3);
	}
};