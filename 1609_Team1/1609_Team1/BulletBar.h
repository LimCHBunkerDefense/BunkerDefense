#pragma once
#include "InputManager.h"
#include "RenderManager.h"
#include "Common.h"

class UIBulletBar
{
	Box2 m_bar;
	Box2 m_frame;

	ColorF m_colorMin;
	ColorF m_colorMax;
	ColorF m_colorBar;
	ColorF m_colorFrame;
	ColorF m_colorBg;

	PROGRESS_STATE m_state;
	float m_value;
	float m_targetValue;

	float m_scale;

	Vector m_originSize;
	Vector m_originLeftTop;

public:
	UIBulletBar(Vector center, Vector size, ColorF barColor, ColorF frameColor) :
		m_bar(center, size * 0.99f),
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
		m_scale = 1.0f;

		SetValue(1.0f);
		SetTargetValue(1.0f);
	}

	void SetMinMaxColor(ColorF minColor, ColorF maxColor)
	{
		m_colorMin = minColor;
		m_colorMax = maxColor;
	}

	float GetValue() { return m_value; }

	void SetValue(float value)
	{
		m_value = MATH->Clamp(value, 0.0f, 1.0f);
		m_bar.size.x = MATH->Lerp(0.0f, m_originSize.x, m_value);
		//m_bar.SetLeftTop(m_originLeftTop);
		m_colorBar.r = MATH->Lerp(m_colorMin.r, m_colorMax.r, m_value);
		m_colorBar.g = MATH->Lerp(m_colorMin.g, m_colorMax.g, m_value);
		m_colorBar.b = MATH->Lerp(m_colorMin.b, m_colorMax.b, m_value);
		m_colorBar.a = MATH->Lerp(m_colorMin.a, m_colorMax.a, m_value);
	}

	void SetCenter(Vector center)
	{
		m_bar.SetCenter(center);
		m_frame.SetCenter(center);
	}

	void SetScale(float scale)
	{
		m_scale = scale;
	}

	void SetTargetValue(float value)
	{
		m_targetValue = MATH->Clamp(value, 0.0f, 1.0f);
	}

	void Update(float deltaTime)
	{
		switch (m_state)
		{
		case PROGRESS_STATE_NONE:
			if (m_value != m_targetValue)
			{
				m_state = PROGRESS_STATE_CHANGE;
			}
			break;

		case PROGRESS_STATE_CHANGE:
			// SetValue(MATH->MoveForward(m_value, m_targetValue, deltaTime));
			SetValue(m_targetValue);
			if (m_value == m_targetValue) m_state = PROGRESS_STATE_NONE;
			break;

		case PROGRESS_STATE_DRAG:
			break;
		}
	}

	void Render()
	{
		RENDER->FillRect(m_frame.center, m_frame.size * m_scale, m_colorBg);
		RENDER->FillRect(m_bar.center, m_bar.size * m_scale, m_colorBar);
		RENDER->DrawRect(m_bar.center, m_bar.size * m_scale, ColorF(1, 1, 1, 0.3f), 2);
		RENDER->DrawRect(m_frame.center, m_frame.size * m_scale, m_colorFrame, 2);
	}

	void Render(Camera* pCamera)
	{
		pCamera->DrawFilledRect(m_frame.center, m_frame.size * m_scale, m_colorBg);
		pCamera->DrawFilledRect(m_bar.center, m_bar.size * m_scale, m_colorBar);
		pCamera->DrawRect(m_bar.center, m_bar.size * m_scale, ColorF(1, 1, 1, 0.3f), 2);
		pCamera->DrawRect(m_frame.center, m_frame.size * m_scale, m_colorFrame, 2);
	}
};