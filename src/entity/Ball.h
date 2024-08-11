#pragma once
#include <SDL.h>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "../util/Constants.h"
#include "../util/Math.h"
#include "../collision/CircleCollider.h"

class Ball
{
private:
	Vector2f m_position;
	Vector2f m_midPoint;
	float m_radius;
	Vector2f m_velocity;
	SDL_Texture* m_texture;
	CircleCollider m_collider;
	float m_arrowRotationAngle;
	float m_speed;
	bool m_isMouseDown;

	// methods
	void Move(float delta);
	float CalculateAngleBetweenPoints(Vector2f start, Vector2f end);
public:
	Ball(Vector2f position, float radius, SDL_Texture* texture);
	//setters
	void SetVelocity(Vector2f velocity) { m_velocity = velocity; }
	void SetArrowRotationAngle(float angle) { m_arrowRotationAngle = angle; }
	//getters
	Vector2f GetPosition() { return m_position; }
	Vector2f GetMidpoint() { return m_midPoint; }
	float GetRadius() { return m_radius; }
	Vector2f GetVelocity() { return m_velocity; }
	SDL_Texture* GetTexture() { return m_texture; }
	CircleCollider GetCollider() { return m_collider; }
	float GetArrowRotationAngle() { return m_arrowRotationAngle; }
	bool IsMouseDown() { return m_isMouseDown; }
	void Update(double delta);
	void Input(SDL_Event event);
	Vector2f GetMousePosAsVector();
};
