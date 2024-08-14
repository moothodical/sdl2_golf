#pragma once
#include <SDL.h>

#include "../util/Math.h"

struct Wall
{
	Vector2f m_position;
	SDL_Texture* m_texture;

	Wall (Vector2f position, SDL_Texture* texture) 
		: m_position(position), m_texture(texture) 
	{
	
	}
};
