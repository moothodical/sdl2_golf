#include <iostream>
#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* title, int width, int height)
	: m_window(NULL), m_renderer(NULL), m_width(width), m_height(height)
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,height, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::LoadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(m_renderer, filePath);

	if(texture == NULL)
		std::cout << "Failed to load a texture" << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::Render(Ball& ball)
{

	float l = ball.GetRadius() * 2;
	SDL_Rect destBall = { ball.GetPosition().x, ball.GetPosition().y, l, l };

	SDL_Texture* pointTexture = LoadTexture("res/point.png");

	//ball
	SDL_RenderCopy(m_renderer, ball.GetTexture(), nullptr, &destBall);
	SDL_RenderCopy(m_renderer, pointTexture, nullptr, &destBall);
	
	// render rotation angle arrow if set
	float ballRotationAngle = ball.GetArrowRotationAngle();
	if (ballRotationAngle != NULL && ball.IsMouseDown())
	{
		RenderArrow(ball, ballRotationAngle);
	}
}

void RenderWindow::RenderArrow(Ball& ball, float angle)
{
    Vector2f mousePos = ball.GetMousePosAsVector();
    Vector2f ballMidpoint = ball.GetMidpoint();
    float initVelocityFactor = 900;
    
    // Calculate distance
    Vector2f direction(mousePos.x - ballMidpoint.x, mousePos.y - ballMidpoint.y);
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    Vector2f normalizedDirection = Utils::Normalize(direction);

    SDL_Texture* arrowTexture = LoadTexture("res/arrow.png");
    
    // Source rectangle (actual arrow area)
    SDL_Rect src = {0, 14, 32, 5};
    
    float scale = distance / src.w;

    // Pivot point (base of the arrow, considering its height)
    SDL_Point pivot = {0, src.h / 2 * scale}; // Use integer values for pivot

    // Destination rectangle
    SDL_Rect dest = {
        static_cast<int>(ballMidpoint.x - pivot.x), 
        static_cast<int>(ballMidpoint.y - pivot.y), 
        static_cast<int>(src.w * scale),                    
        static_cast<int>(src.h * scale)                     
    };
    
    angle = atan2(direction.y, direction.x) * 180 / M_PI; // Convert radians to degrees
    angle += 180; // Invert angle by adding 180 degrees
    if (angle >= 360) {
        angle -= 360; // Normalize angle to be within [0, 360) range
    }
   
    Vector2f ballVelocity(normalizedDirection.x * scale * initVelocityFactor, normalizedDirection.y * scale * initVelocityFactor);
    ball.SetVelocity(ballVelocity);
   
    // Render the arrow
    SDL_RenderCopyEx(m_renderer, arrowTexture, &src, &dest, angle, &pivot, SDL_FLIP_NONE);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(m_renderer);
}

void RenderWindow::Cleanup() 
{
	SDL_DestroyWindow(m_window);
}

void RenderWindow::Display() 
{
	SDL_RenderPresent(m_renderer);
}


