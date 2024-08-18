#pragma once

#include <SDL.h>

struct Hole
{
	Vector2f m_position;
	float m_radius;
	SDL_Texture* m_texture;
	Hole() : m_position(Vector2f()), m_radius(0), m_texture(nullptr) {}
	Hole(Vector2f position, float radius, SDL_Texture* texture) : m_position(position), m_radius(radius), m_texture(texture) {}
};
