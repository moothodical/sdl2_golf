#pragma once

#include <vector>

#include "util/Math.h"
#include "entity/Hole.h"
#include "entity/Wall.h"

struct Level
{
	int m_levelId;
	Vector2f m_ballLoc;
	std::vector<Wall> m_walls;
	Hole m_hole;

	Level() : m_levelId(), m_ballLoc(), m_walls(), m_hole() {}
	Level(int levelId, Vector2f ballLoc, std::vector<Wall> walls, Hole hole) :
		m_levelId(levelId),
		m_ballLoc(ballLoc),
		m_walls(walls),
		m_hole(hole)
		{ }
};
