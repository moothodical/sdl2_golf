#include "Math.h"

namespace Utils
{
    Vector2f Utils::Normalize(const Vector2f& v)
	{
        float length = sqrt(v.x * v.x + v.y * v.y);
        if (length != 0) {
            return { v.x / length, v.y / length };
        }
        return { 0, 0 }; // Return zero vector if length is zero
    }

    float Utils::Magnitude(const Vector2f& v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

}