#include "SceneManager.h"



SceneManager::SceneManager()
{
	m_current = 0;
}


SceneManager::~SceneManager()
{
}

// ¾À µî·Ï
void SceneManager::Register(int tag, IScene* pScene)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		m_scenes[tag] = pScene;
	}
}

// ¾À ¹ÝÈ¯
IScene* SceneManager::GetScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end()) return NULL;
	return m_scenes[tag];
}

// ¾À º¯°æ
void SceneManager::ChangeScene(int tag)
{
	if (m_current != tag)
	{
		IScene* prevScene = GetScene(m_current);
		if (prevScene != NULL) prevScene->OnExit();

		IScene* nextScene = GetScene(tag);
		if (nextScene != NULL) nextScene->OnEnter();

		m_current = tag;
	}
}

// ¾À ¾÷µ¥ÀÌÆ®
void SceneManager::Update(float deltaTime)
{
	IScene* currentScene = GetScene(m_current);
	if (currentScene != NULL) currentScene->OnUpdate(deltaTime);
}

// ¾À µå·Î¿ì
void SceneManager::Draw()
{
	IScene* currentScene = GetScene(m_current);
	if (currentScene != NULL) currentScene->OnDraw();
}