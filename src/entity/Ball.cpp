#include "Ball.h"
#include "../util/Math.h"

Ball::Ball(Vector2f position, float radius, SDL_Texture* texture)
	: m_position(position),
	m_radius(radius),
	m_velocity(Vector2f(0, 0)),
	m_texture(texture),
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
        if (e.button.button == SDL_BUTTON_LEFT && m_velocity.x < 1 && m_velocity.y < 1)
        {
			mouseDownPos = GetMousePosAsVector();
			m_isMouseDown = true;
        }
    }

    if (e.type == SDL_MOUSEBUTTONUP)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
			m_isMouseDown = false;
        }
        //mouseUpPos = GetMousePosAsVector();
        //distance = sqrt(pow(mouseDownPos.x, 2) - pow(mouseUpPos.x, 2) + pow(mouseDownPos.y, 2) - pow(mouseUpPos.y, 2));
        //float angle = CalculateAngleBetweenPoints(m_midPoint, mouseUpPos);
        //SetArrowRotationAngle(angle);

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
    if (x < 0) 
        x = 0;
    if (y < 0) 
        y = 0;
    if (x >= WINDOW_WIDTH) 
        x = WINDOW_WIDTH - 1;
    if (y >= WINDOW_HEIGHT) 
        y = WINDOW_HEIGHT - 1;
    float fx = static_cast<float>(x);
    float fy = static_cast<float>(y);
    return Vector2f(fx, fy);
}

void Ball::Move(float delta)
{
    float spinFactor = 1.05;
    //Vector2f spinEffect(m_spin.x * spinFactor, m_spin.y * spinFactor);

    ApplyFriction(delta);
    //std::cout << m_velocity.x << ", " << m_velocity.y << std::endl;

    //if (m_isMouseDown)
    //{
     m_position.x += m_velocity.x * delta;
     m_position.y += m_velocity.y * delta;
     CheckWindowCollision();
    //}
    //else
    //{
        //m_position.x += (m_velocity.x + spinEffect.x) * delta;
        //m_position.y += (m_velocity.y + spinEffect.y) * delta;
    //}
    }
void Ball::ApplyFriction(float deltaTime)
{
    const float highSpeedThreshold = 1000;
    const float lowSpeedThreshold = 500;
    const float highFriction = 1000;
    const float lowFriction = 250;
    float speed = Utils::Magnitude(m_velocity);

    float friction;
    if (speed > highSpeedThreshold)
    {
        friction = highFriction;
    }
    else if (speed < lowSpeedThreshold)
    {
        friction = lowFriction;
    }
    else
    {
         // Linear interpolation for friction
        float frictionRange = highFriction - lowFriction;
        float speedRange = highSpeedThreshold - lowSpeedThreshold;
        float speedNormalized = (speed - lowSpeedThreshold) / speedRange;
        friction = lowFriction + (frictionRange * speedNormalized);
    }

    if (speed > 0) {

        Vector2f normalizedVelocity = Utils::Normalize(m_velocity);
        Vector2f frictionForce(normalizedVelocity.x * friction, normalizedVelocity.y * friction);
       
        m_velocity.x -= frictionForce.x * deltaTime;
        m_velocity.y -= frictionForce.y * deltaTime;

        if (Utils::Magnitude(m_velocity) < 0.1f) { 
            m_velocity = { 0, 0 };
        }
    }
}

void Ball::CheckWindowCollision()
{
    float xRadPosRight = m_position.x + m_radius;
    float xRadPosLeft = m_position.x - m_radius;
    float yRadPosUp = m_position.y - m_radius;
    float yRadPosDown = m_position.y + m_radius;

    Vector2f collisionPoint;
    if (xRadPosRight > WINDOW_WIDTH)
    {
        collisionPoint = Vector2f(WINDOW_WIDTH, m_position.y);
        float distance = Utils::DistanceSquared(m_position, collisionPoint);
        Reflect(collisionPoint, distance);
    }
    if (xRadPosLeft < 0)    {
        collisionPoint = Vector2f(0, m_position.y);
        float distance = Utils::DistanceSquared(m_position, collisionPoint);
        Reflect(collisionPoint, distance);
    }
    if (yRadPosUp < 0)
    {
        collisionPoint = Vector2f(m_position.x, 0);
        float distance = Utils::DistanceSquared(m_position, collisionPoint);
        Reflect(collisionPoint, distance);
    }
    if (yRadPosDown > WINDOW_HEIGHT)
    {
        collisionPoint = Vector2f(m_position.x, WINDOW_HEIGHT);
        float distance = Utils::DistanceSquared(m_position, collisionPoint);
        Reflect(collisionPoint, distance);
    }
}

void Ball::CheckWallCollision(std::vector<Wall>& walls)
{
    for (Wall& wall : walls)
    {
        Vector2f closestPoint = ClosestPointOnRect(wall);
        float distance = Utils::DistanceSquared(m_position, closestPoint);
        
        if (distance <= m_radius * m_radius)
        {
            Reflect(closestPoint, distance);
        }
    }
}

bool Ball::CheckHoleCollision(Hole& hole)
{
    float distance = Utils::DistanceSquared(m_position, hole.m_position);
    float sumSquared = pow(m_radius + hole.m_radius, 2);
    if (distance < sumSquared)
    {
        SoundManager::GetInstance()->PlaySound("hole");
        return true;
    }
    return false;
}

void Ball::Reflect(Vector2f collisionPoint, float distance)
{
    SoundManager::GetInstance()->PlayHitWallSound(Utils::Magnitude(m_velocity));
	std::cout << "Collision at: " << collisionPoint.x << ", " << collisionPoint.y << std::endl;
	Vector2f collisionNormal(m_position.x - collisionPoint.x, m_position.y - collisionPoint.y);
	float magnitude = Utils::Magnitude(collisionNormal);
	collisionNormal = Utils::Normalize(collisionNormal);

	float dotProduct = m_velocity.x * collisionNormal.x + m_velocity.y * collisionNormal.y;
	m_velocity.x -= 2 * dotProduct * collisionNormal.x;
	m_velocity.y -= 2 * dotProduct * collisionNormal.y;

	float overlap = m_radius - std::sqrt(distance);
	m_position.x += overlap * collisionNormal.x;
	m_position.y += overlap * collisionNormal.y;
}

void Ball::StopAndPlace(Vector2f position)
{
    m_velocity = Vector2f(0, 0);
    m_position = position;
}

Vector2f Ball::ClosestPointOnRect(Wall& wall)
{
    float closestX = m_position.x;
    if (m_position.x < wall.m_xLeft) {
        closestX = wall.m_xLeft; 
    } else if (m_position.x > wall.m_xRight) {
        closestX = wall.m_xRight; 
    }

    float closestY = m_position.y;
    if (m_position.y < wall.m_yUp) {
        closestY = wall.m_yUp; 
    } else if (m_position.y > wall.m_yDown) {
        closestY = wall.m_yDown; 
    }    
    return Vector2f(closestX, closestY);
}

void Ball::Update(double delta)
{
    if (delta <= 0.0)
    {
        return;
    }
     
    if (m_isMouseDown)
    {
        Vector2f mousePos = GetMousePosAsVector();
        float angle = CalculateAngleBetweenPoints(m_position, mousePos);
        SetArrowRotationAngle(angle);
    }
    else {
        Move(delta);
    }
        


    // Debug output
    // std::cout << "Position before: " << m_position.x << " " << m_position.y << std::endl;
    // std::cout << "Position after: " << m_position.x << " " << m_position.y << std::endl;
}