#include "Ball.h"

Ball::Ball(Vector2f position, float radius, SDL_Texture* texture)
	: m_position(position),
    m_midPoint(Vector2f(position.x + radius, position.y - radius)),
	m_radius(radius),
	m_velocity(Vector2f(0, 0)),
	m_texture(texture),
	m_collider(CircleCollider(position, radius)),
    m_speed(500)
{

}
 
void Ball::Input(SDL_Event e)
{
    Vector2f mouseDownPos;
    Vector2f mouseUpPos; 
    float distance;
    
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        mouseDownPos = GetMousePosAsVector();
        m_isMouseDown = true;
    }


    if (e.type == SDL_MOUSEBUTTONUP)
    {
        //mouseUpPos = GetMousePosAsVector();
        //distance = sqrt(pow(mouseDownPos.x, 2) - pow(mouseUpPos.x, 2) + pow(mouseDownPos.y, 2) - pow(mouseUpPos.y, 2));
        //float angle = CalculateAngleBetweenPoints(m_midPoint, mouseUpPos);
        //SetArrowRotationAngle(angle);
        m_isMouseDown = false;

        //std::cout << angle << std::endl;
    }
}

float Ball::CalculateAngleBetweenPoints(Vector2f start, Vector2f end)
{
    return atan2(end.y - start.y, end.x - start.x) * 180.0f / M_PI;
}

Vector2f Ball::GetMousePosAsVector()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    float fx = static_cast<float>(x);
    float fy = static_cast<float>(y);
    return Vector2f(fx, fy);
}

void Ball::Move(float delta)
{
    float friction = 0.98;
    m_position.x += m_velocity.x * delta * friction;
    m_position.y += m_velocity.y * delta * friction;
    m_midPoint.x = m_position.x + m_radius;
    m_midPoint.y = m_position.y + m_radius;

    // calculate the x + radius and y + radius
    float xRadPosRight = m_midPoint.x + m_radius;
    float xRadPosLeft = m_midPoint.x - m_radius;
    float yRadPosUp = m_midPoint.y - m_radius;
    float yRadPosDown = m_midPoint.y + m_radius;

    if (xRadPosRight > WINDOW_WIDTH)
    {
        m_velocity.x = -m_velocity.x; // Reflect the velocity
        m_position.x += m_velocity.x * delta;
        std::cout << "position: " << m_position.x << ", " << m_position.y << std::endl;
    }
    if (xRadPosLeft < 0)    {
        m_velocity.x = -m_velocity.x; // Reflect the velocity
        m_position.x -= m_velocity.x * delta;
        std::cout << "position: " << m_position.x << ", " << m_position.y << std::endl;
    }
    if (yRadPosUp < 0)
    {
        m_velocity.y = -m_velocity.y; // Reflect the velocity
        m_position.y += m_velocity.y * delta;
        std::cout << "position: " << m_position.x << ", " << m_position.y << std::endl;
    }
    if (yRadPosDown > WINDOW_HEIGHT)    
    {
        m_velocity.y = -m_velocity.y; // Reflect the velocity
        m_position.y -= m_velocity.y * delta;
        std::cout << "position: " << m_position.x << ", " << m_position.y << std::endl;
    }

    m_midPoint.x = m_position.x + m_radius;
    m_midPoint.y = m_position.y + m_radius;
}

void Ball::Update(double delta)
{
    // Skip over delta = 0 case
    if (delta <= 0.0)
    {
        return;
    }
      
    if (m_isMouseDown)
    {
        Vector2f mousePos = GetMousePosAsVector();
        float angle = CalculateAngleBetweenPoints(m_midPoint, mousePos);
        SetArrowRotationAngle(angle);
    }
    Move(delta);


    // Debug output
    // std::cout << "Position before: " << m_position.x << " " << m_position.y << std::endl;
    // std::cout << "Position after: " << m_position.x << " " << m_position.y << std::endl;
}