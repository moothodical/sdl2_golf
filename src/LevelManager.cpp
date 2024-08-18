#include "LevelManager.h"

LevelManager::LevelManager()
	: m_currentLevel(),
	m_textures(),
	m_ballLoc(),
	m_walls(),
	m_holes()
{
}

void LevelManager::Init(std::unordered_map<std::string, SDL_Texture*> textures)
{
	m_textures = textures;
	LoadLevels();
	m_currentLevel = LoadLevel(1);
}

void LevelManager::LoadLevels()
{
	m_ballLoc.emplace(1, Vector2f(250, 300));
	m_ballLoc.emplace(2, Vector2f(100, 250));

	m_walls[1].push_back(Wall(Vector2f(100, 200), m_textures.at("wall")));
	m_walls[1].push_back(Wall(Vector2f(300, 400), m_textures.at("wall")));
	m_walls[2].push_back(Wall(Vector2f(600, 400), m_textures.at("wall")));
	m_walls[2].push_back(Wall(Vector2f(220, 300), m_textures.at("wall")));
	m_walls.emplace(1, m_walls[1]);
	m_walls.emplace(2, m_walls[2]);

	m_holes.emplace(1, Hole(Vector2f(900, 500), 15, m_textures.at("hole")));
	m_holes.emplace(2, Hole(Vector2f(100, 100), 15, m_textures.at("hole")));
}

Level LevelManager::LoadNextLevel()
{
	return LoadLevel(m_currentLevel.m_levelId+1);
}

Level LevelManager::LoadLevel(int level)
{
	return Level(level, m_ballLoc[level], m_walls[level], m_holes[level]);
}