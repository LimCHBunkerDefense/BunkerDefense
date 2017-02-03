#pragma once
#include "Singleton.h"
#include "fmod/fmod.hpp"
#include "Common.h"
#include <map>
#include <list>
#pragma comment (lib, "fmod/fmodex_vc.lib")
using namespace FMOD;
using namespace std;

#define SOUND SoundManager::Instance()


class SoundManager : public Singleton<SoundManager>
{
	System* m_pSystem;
	map<string, Sound*> m_sounds;
	list<Channel*> m_channels;

public:
	SoundManager();
	~SoundManager();

	void Init();
	void Release();
	void Update(float deltaTime);
	Sound* FindSound(string key);
	void LoadFile(string key, string filename, bool bgm);
	void Play(string key, float volume = 1.0f);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	Channel* FindChannel(string key);
};