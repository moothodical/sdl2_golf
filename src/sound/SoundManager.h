#pragma once
#include <SDL_mixer.h>
#include <unordered_map>
#include <string>

class SoundManager
{
private:
	SoundManager();
private:
	static SoundManager* m_instance;
	std::unordered_map<std::string, Mix_Chunk*> m_sounds;
public:
	void Cleanup();
	static SoundManager* GetInstance();
    bool LoadSounds();
	void PlaySound(std::string sound);
	void PlayHitWallSound(float speed);
};
