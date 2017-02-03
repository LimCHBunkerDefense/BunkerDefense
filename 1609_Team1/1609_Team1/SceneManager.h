#pragma once
#include "Singleton.h"
#include <map>
using namespace std;

#define SCENE SceneManager::Instance()

class IScene
{
public:
	virtual void OnEnter() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnExit() = 0;
	virtual void OnDraw() = 0;
};

class SceneManager : public Singleton<SceneManager>
{
	map<int, IScene*> m_scenes;
	int m_current;

public:
	SceneManager();
	~SceneManager();

	// ¾À µî·Ï
	void Register(int tag, IScene* pScene);

	// ¾À ¹ÝÈ¯
	IScene* GetScene(int tag);

	// ¾À º¯°æ
	void ChangeScene(int tag);

	// ¾À ¾÷µ¥ÀÌÆ®
	void Update(float deltaTime);

	// ¾À µå·Î¿ì
	void Draw();
};