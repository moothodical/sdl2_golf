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
	bool m_init;
	int m_currentLevel;
	std::unordered_map<std::string, SDL_Texture*> m_textures;
	std::unordered_map<int, Vector2f> m_ballLoc;
	std::unordered_map<int, std::vector<Wall>> m_walls;
	std::unordered_map<int, Hole> m_holes;
public:
	LevelManager();
	void SetTextures(std::unordered_map<std::string, SDL_Texture*> textures);
	void LoadLevels();
	Level LoadLevel(int level);
};
