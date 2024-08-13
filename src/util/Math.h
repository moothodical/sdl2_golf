#pragma once
#include <iostream>

struct Vector2f
{
	Vector2f()
		:x(0.0f), y(0.0)
	{}
	Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
	{}

	float x, y;
	void print ()
	{
		std::cout << x << " " << y << std::endl;
	}
};

namespace Utils
{
	Vector2f Normalize(const Vector2f& v);
	float Magnitude(const Vector2f& v);
}


