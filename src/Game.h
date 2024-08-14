#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <unordered_map>
#include <string>

#include "util/Constants.h"
#include "entity/Ball.h"
#include "entity/Wall.h"
#include "render/RenderWindow.h"

class Game
{
private:
	RenderWindow m_window;
	std::unordered_map<std::string, SDL_Texture*> m_textures;
	std::vector<Wall> m_walls;
public:
	Game();
	~Game();
	bool Init();
	void InitObjects();
	void LoadTextures();
	void Run();
	void CleanUp();
};
