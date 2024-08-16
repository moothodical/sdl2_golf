#include "LevelManager.h"

LevelManager::LevelManager()
	: m_currentLevel(1)
{
}

void LevelManager::SetTextures(std::unordered_map<std::string, SDL_Texture*> textures)
{
	m_textures = textures;
}

void LevelManager::LoadLevels()
{
	m_ballLoc = std::unordered_map<int, Vector2f> {
		{1, Vector2f(250, 300)},
		{2, Vector2f(100, 250)}
	};

	m_walls = std::unordered_map<int, std::vector<Wall>> {
		{1, {
			Wall(Vector2f(100, 200), m_textures.at("wall")),
			Wall(Vector2f(600, 500), m_textures.at("wall"))
		}},
		{2, {
			Wall(Vector2f(400, 625), m_textures.at("wall")),
			Wall(Vector2f(1000, 350), m_textures.at("wall")),
		}}
	};

	m_holes = std::unordered_map<int, Hole>{
		{1, Hole(Vector2f(900, 750))}
	};
}

Level LevelManager::LoadLevel(int level)
{
	return Level(m_ballLoc[level], m_walls[level]);
}