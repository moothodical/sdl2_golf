#pragma once

#include <unordered_map>
#include <vector>

#include "Level.h"
#include "util/Math.h"
#include "entity/Wall.h"
#include "entity/Hole.h"

class LevelManager
{
private:
	Level m_currentLevel;
	std::unordered_map<std::string, SDL_Texture*> m_textures;
	std::unordered_map<int, Vector2f> m_ballLoc;
	std::unordered_map<int, std::vector<Wall>> m_walls;
	std::unordered_map<int, Hole> m_holes;
public:
	LevelManager();
	void Init(std::unordered_map<std::string, SDL_Texture*> textures);
	Level GetCurrentLevel() { return m_currentLevel; }
	void LoadLevels();
	Level LoadNextLevel();
	Level LoadLevel(int level);
};
