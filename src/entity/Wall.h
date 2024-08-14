#pragma once
#include <SDL.h>

#include "../util/Math.h"

struct Wall
{
	Vector2f m_position;
	SDL_Rect m_bounds;
	float m_xLeft, m_xRight, m_yUp, m_yDown;
	SDL_Texture* m_texture;

	Wall (Vector2f position, SDL_Texture* texture) 
		: m_position(position),
		m_bounds(SDL_Rect {static_cast<int>(position.x), static_cast<int>(position.y), 32, 64}),
		m_xLeft(position.x), 
		m_xRight(position.x + 32), 
		m_yUp(position.y), 
		m_yDown(position.y + 64), 
		m_texture(texture) 
	{
	
	}
};
