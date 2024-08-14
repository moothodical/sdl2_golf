#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <unordered_map>
#include <SDL_ttf.h>
#include <string>

#include "util/Constants.h"
#include "entity/Ball.h"
#include "entity/Wall.h"
#include "render/RenderWindow.h"
#include "Grid.h"

class Game
{
private:
	RenderWindow m_window;
	Grid m_grid;
	TTF_Font* m_font;
	std::unordered_map<std::string, SDL_Texture*> m_textures;
	std::unordered_map<std::string, SDL_Surface*> m_surfaces;
	std::vector<Wall> m_walls;
public:
	enum class GameState
	{
		PLAY,
		LEVEL_EDIT
	};

	Game();
	~Game();
	bool Init();
	void InitObjects();
	void LoadTextures();
	void Run();
	void CleanUp();
	void SetGameState(Game::GameState gameState);
	const char* GetGameStateText();
	void UpdateGameStateText();
private:
	GameState m_gameState;
};
