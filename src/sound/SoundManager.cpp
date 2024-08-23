#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::m_instance = nullptr;

SoundManager::SoundManager()
{
	LoadSounds();
}

void SoundManager::Cleanup()
{
	std::cout << "destrutor callet" << std::endl;
	Mix_HaltChannel(-1); 
	
	for (const auto& pair : m_sounds)
	{
		Mix_FreeChunk(pair.second);
	}

	Mix_CloseAudio();
	Mix_Quit();
}

SoundManager* SoundManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new SoundManager();
	}
	return m_instance;
}

bool SoundManager::LoadSounds()
{
	Mix_Chunk* swing = Mix_LoadWAV("res/sound/swing.wav");
	if (swing == NULL)
	{
		return false;
	}
	m_sounds.emplace("swing", swing);

	Mix_Chunk* swingUp = Mix_LoadWAV("res/sound/swing_up.wav");
	if (swingUp == NULL)
	{
		return false;
	}
	m_sounds.emplace("swing_up", swingUp);

	Mix_Chunk* swingDown = Mix_LoadWAV("res/sound/swing_down.wav");
	if (swingDown == NULL)
	{
		return false;
	}
	m_sounds.emplace("swing_down", swingDown);

	Mix_Chunk* hole = Mix_LoadWAV("res/sound/hole.wav");
	if (hole == NULL)
	{
		return false;
	}
	m_sounds.emplace("hole", hole);

	Mix_Chunk* hitWallHigh = Mix_LoadWAV("res/sound/hit_wall_high_vel.wav");
	if (hitWallHigh == NULL)
	{
		return false;
	}
	m_sounds.emplace("hit_wall_high_vel", hitWallHigh);
	
	Mix_Chunk* hitWallMed = Mix_LoadWAV("res/sound/hit_wall_med_vel.wav");
	if (hitWallMed == NULL)
	{
		return false;
	}
	m_sounds.emplace("hit_wall_med_vel", hitWallMed);

	Mix_Chunk* hitWallLow = Mix_LoadWAV("res/sound/hit_wall_low_vel.wav");
	if (hitWallLow == NULL)
	{
		return false;
	}
	m_sounds.emplace("hit_wall_low_vel", hitWallMed);

	return true;

}

void SoundManager::PlaySound(std::string sound)
{
	auto found = m_sounds.find(sound);
	if (found != m_sounds.end())
	{
		Mix_PlayChannel(-1, m_sounds.at(sound), 0);
	}
	else
	{
		std::cout << "Sound " << sound << " not found." << std::endl;
	}

}

void SoundManager::PlayHitWallSound(float speed)
{
	const float high = 1500;
	const float med = 500;

	if (speed > high)
	{
		PlaySound("hit_wall_high_vel");
	}
	else if (speed > med)
	{
		PlaySound("hit_wall_med_vel");
	}
	else
	{
		PlaySound("hit_wall_low_vel");
	}
}