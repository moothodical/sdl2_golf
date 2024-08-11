#pragma once

#include "../util/Math.h"

struct CircleCollider
{
	CircleCollider(Vector2f position, float radius) : m_position(position), m_radius(radius) { }
	Vector2f m_position;
	float m_radius;
};
