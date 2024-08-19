#pragma once
#include <SDL.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include "Wall.h"
#include "Hole.h"
#include "../util/Constants.h"
#include "../util/Math.h"
#include "../collision/CircleCollider.h"

class Ball
{
private:
	Vector2f m_position;
	float m_radius;
	Vector2f m_velocity;
	Vector2f m_spin;
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
	void SetVelocity(Vector2f velocity) 
	{ 
		m_velocity = velocity; 
		m_spin = Vector2f(-m_velocity.y, m_velocity.x);
	}
	void SetArrowRotationAngle(float angle) { m_arrowRotationAngle = angle; }
	//getters
	Vector2f GetPosition() { return m_position; }
	float GetRadius() { return m_radius; }
	Vector2f GetVelocity() { return m_velocity; }
	SDL_Texture* GetTexture() { return m_texture; }
	CircleCollider GetCollider() { return m_collider; }
	float GetArrowRotationAngle() { return m_arrowRotationAngle; }
	bool IsMouseDown() { return m_isMouseDown; }
	void Update(double delta);
	void Input(SDL_Event event);
	void ApplyFriction(float deltaTime);
	void CheckWindowCollision();
	void CheckWallCollision(std::vector<Wall>& walls);
	bool CheckHoleCollision(Hole& hole);
	void Reflect(Vector2f collisionPoint, float distance);
	void StopAndPlace(Vector2f position);
	Vector2f ClosestPointOnRect(Wall& wall);
	Vector2f GetMousePosAsVector();
};
