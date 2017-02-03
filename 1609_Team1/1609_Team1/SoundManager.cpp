#include "SoundManager.h"



SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::Init()
{
	System_Create(&m_pSystem);
	m_pSystem->init(SOUND_MAX_CHANNEL, FMOD_INIT_NORMAL, 0);
}

void SoundManager::Release()
{
	m_pSystem->release();
	m_pSystem->close();
}

void SoundManager::Update(float deltaTime)
{
	m_pSystem->update();

	list<Channel*>::iterator it;
	for (it = m_channels.begin(); it != m_channels.end(); it++)
	{
		bool isPlaying;
		(*it)->isPlaying(&isPlaying);
		if (!isPlaying)
		{
			m_channels.erase(it);
			break;
		}
	}
}

Sound* SoundManager::FindSound(string key)
{
	if (m_sounds.find(key) == m_sounds.end()) return NULL;
	return m_sounds[key];
}

void SoundManager::LoadFile(string key, string filename, bool bgm)
{
	Sound* pSound = FindSound(key);
	if (pSound != NULL) return;

	if (bgm)
	{
		m_pSystem->createStream(filename.c_str(),
			FMOD_LOOP_NORMAL, NULL, &pSound);
	}
	else
	{
		m_pSystem->createSound(filename.c_str(),
			FMOD_DEFAULT, NULL, &pSound);
	}

	if (pSound != NULL) m_sounds[key] = pSound;
}

void SoundManager::Play(string key, float volume = 1.0f)
{
	Sound* pSound = FindSound(key);
	if (pSound == NULL) return;

	Channel* pChannel;
	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, &pChannel);
	if (pChannel == NULL) return;

	pChannel->setVolume(volume);
	m_channels.push_back(pChannel);
}

void SoundManager::Stop(string key)
{
	Channel* pChannel = FindChannel(key);
	if (pChannel != NULL) pChannel->stop();
}

void SoundManager::Pause(string key)
{
	Channel* pChannel = FindChannel(key);
	if (pChannel != NULL) pChannel->setPaused(true);
}

void SoundManager::Resume(string key)
{
	Channel* pChannel = FindChannel(key);
	if (pChannel != NULL) pChannel->setPaused(false);
}

Channel* SoundManager::FindChannel(string key)
{
	Sound* pSound = FindSound(key);
	if (pSound == NULL) return NULL;

	list<Channel*>::iterator it;
	for (it = m_channels.begin(); it != m_channels.end(); it++)
	{
		Sound* pCurrentSound;
		(*it)->getCurrentSound(&pCurrentSound);
		if (pCurrentSound == pSound) return (*it);
	}
	return NULL;
}