#pragma once

#include <vector>

#include "util/Math.h"
#include "entity/Hole.h"
#include "entity/Wall.h"

struct Level
{
	Vector2f m_ballLoc;
	std::vector<Wall> m_walls;

	Level(Vector2f ballLoc, std::vector<Wall> walls) : 
		m_ballLoc(ballLoc), 
		m_walls(walls)
		{ }
};
