#pragma once
#include "RenderManager.h"
#include <vector>
#include <map>
using namespace std;

class Animation
{
	vector<Sprite*> m_sprites;
	float m_frameTime;
	float m_elapsedTime;
	int m_spriteCount;
	int m_currentIndex;
	bool m_isLoop;

public:
	Animation(wstring imageKey, int imageCount, int fps, bool loop,
		float scale = 1.0f, float anchorX = 0.5f, float anchorY = 0.5f)
	{
		TCHAR key[100] = {};
		for (int i = 0; i < imageCount; i++)
		{
			wsprintf(key, TEXT("%s%d"), imageKey.c_str(), i);
			m_sprites.push_back(new Sprite(RENDER->GetImage(key), scale, anchorX, anchorY));
		}

		m_frameTime = 1.0f / (float)fps;
		m_elapsedTime = 0.0f;
		m_spriteCount = imageCount;
		m_currentIndex = 0;
		m_isLoop = loop;
	}

	Sprite* GetSprite() { return m_sprites[m_currentIndex]; }
	bool IsLoop() { return m_isLoop; }
	float GetX() { return GetSprite()->GetLeftX(); }
	float GetY() { return GetSprite()->GetTopY(); }
	float GetWidth() { return GetSprite()->GetWidth(); }
	float GetHeight() { return GetSprite()->GetHeight(); }

	void Reset()
	{
		m_currentIndex = 0;
		m_elapsedTime = 0;
	}

	bool Update(float deltaTime)
	{
		m_elapsedTime += deltaTime;
		if (m_elapsedTime >= m_frameTime)
		{
			m_elapsedTime -= m_frameTime;

			++m_currentIndex;
			if (m_currentIndex >= m_spriteCount)
			{
				m_currentIndex = 0;
				return true;
			}
		}
		return false;
	}
};

class AnimationController
{
	map<int, Animation*> m_animations;
	int m_default;
	int m_current;

public:
	AnimationController()
	{
		m_default = 0;
		m_current = 0;
	}

	~AnimationController()
	{
		map<int, Animation*>::iterator it;
		for (it = m_animations.begin(); it != m_animations.end(); it++)
		{
			delete it->second;
		}
		m_animations.clear();
	}

	// 애니메이션 등록
	void Register(int tag, Animation* pAnim)
	{
		if (m_animations.find(tag) == m_animations.end())
		{
			if (m_animations.size() == 0)
			{
				m_default = tag;
				m_current = tag;
			}
			m_animations[tag] = pAnim;
		}
	}

	// 애니메이션 반환
	Animation* Get(int tag)
	{
		if (m_animations.find(tag) == m_animations.end()) return NULL;
		return m_animations[tag];
	}

	// 현재 애니메이션 반환
	Animation* Current()
	{
		return Get(m_current);
	}

	// 현재 애니메이션 태그 반환
	int CurrentTag()
	{
		return m_current;
	}

	// 애니메이션 플레이
	void Play(int tag)
	{
		if (m_current != tag)
		{
			m_current = tag;
			m_animations[tag]->Reset();
		}
	}

	// 업데이트
	void Update(float deltaTime)
	{
		Animation* pAnim = Current();
		if (pAnim != NULL && pAnim->Update(deltaTime))
		{
			if (!pAnim->IsLoop()) Play(m_default);
		}
	}
};