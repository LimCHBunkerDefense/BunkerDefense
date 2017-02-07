#include "SceneManager.h"



SceneManager::SceneManager()
{
	m_current = 0;

	// �浹ü on/off 
	m_colliderOn = false;
}


SceneManager::~SceneManager()
{
}

// �� ���
void SceneManager::Register(int tag, IScene* pScene)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		m_scenes[tag] = pScene;
	}
}

// �� ��ȯ
IScene* SceneManager::GetScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end()) return NULL;
	return m_scenes[tag];
}

// �� ����
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

// �� ������Ʈ
void SceneManager::Update(float deltaTime)
{
	IScene* currentScene = GetScene(m_current);
	if (currentScene != NULL) currentScene->OnUpdate(deltaTime);
}

// �� ��ο�
void SceneManager::Draw()
{
	IScene* currentScene = GetScene(m_current);
	if (currentScene != NULL) currentScene->OnDraw();
}