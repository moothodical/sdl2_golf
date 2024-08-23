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
	SDL_Rect destBall = { ball.GetPosition().x - ball.GetRadius(), ball.GetPosition().y - ball.GetRadius(), l, l};

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
    
    SDL_DestroyTexture(pointTexture);
}

void RenderWindow::Render(Wall& wall)
{
	SDL_Rect dest = { wall.m_position.x, wall.m_position.y, 32, 64};
    SDL_RenderCopy(m_renderer, wall.m_texture, nullptr, &dest);
}

void RenderWindow::Render(Hole& hole)
{
	SDL_Rect dest = { hole.m_position.x - hole.m_radius / 2, hole.m_position.y - hole.m_radius / 2, hole.m_radius, hole.m_radius};
    SDL_RenderCopy(m_renderer, hole.m_texture, nullptr, &dest);
}

void RenderWindow::Render(Grid& grid)
{
    int increment = grid.m_step;
    int linesX = WINDOW_HEIGHT / 32;
    int linesY = WINDOW_WIDTH / 32;

    for (int i = 0; i < linesX; i++)
    {
        SDL_RenderDrawLine(m_renderer, 0, increment, WINDOW_WIDTH, increment);
        increment += grid.m_step;
    }
    increment = grid.m_step;

    for (int i = 0; i < linesY; i++)
    {
        SDL_RenderDrawLine(m_renderer, increment, 0, increment, WINDOW_HEIGHT);
        increment += grid.m_step;
    }
}

void RenderWindow::Render(SDL_Texture* texture)
{
    SDL_RenderCopy(m_renderer, texture, nullptr, nullptr);
}

SDL_Rect RenderWindow::GetTextRect(Vector2f position, SDL_Texture* texture)
{
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dest = { position.x, position.y, texW, texH };

    std::vector<std::string> e = { "hi", "there" };
    return dest;
}

void RenderWindow::RenderGameStateText(SDL_Texture* label, SDL_Texture* value)
{
    const SDL_Rect& labelRect = GetTextRect(Vector2f(0, 0), label);
    const SDL_Rect& valueRect = GetTextRect(Vector2f(labelRect.x + labelRect.w + 20, labelRect.y), value);
    SDL_RenderCopy(m_renderer, label, NULL, &labelRect);
    SDL_RenderCopy(m_renderer, value, NULL, &valueRect);
}
void RenderWindow::RenderArrow(Ball& ball, float angle)
{
    Vector2f mousePos = ball.GetMousePosAsVector();
    float initVelocityFactor = 200;
    
    Vector2f direction(mousePos.x - ball.GetPosition().x, mousePos.y - ball.GetPosition().y);
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    Vector2f normalizedDirection = Utils::Normalize(direction);

    SDL_Texture* arrowTexture = LoadTexture("res/arrow.png");
    
    SDL_Rect src = {0, 14, 32, 5};
    
    float scale = distance / src.w;

    SDL_Point pivot = {0, src.h / 2 * scale}; // Use integer values for pivot

    SDL_Rect dest = {
        static_cast<int>(ball.GetPosition().x - pivot.x),
        static_cast<int>(ball.GetPosition().y - pivot.y),
        static_cast<int>(src.w * scale),                    
        static_cast<int>(src.h * scale)                     
    };
    // Invert the angle
    angle += 180;
    if (angle >= 360) {
        angle -= 360; 
    }

    // Convert the angle back to a direction vector
    float angleRad = angle * M_PI / 180; // Convert degrees to radians
    Vector2f invertedDirection = { cos(angleRad), sin(angleRad) };

    // Scale the direction vector by the desired velocity
    Vector2f ballVelocity = { invertedDirection.x * scale * initVelocityFactor,
                              invertedDirection.y * scale * initVelocityFactor };

    // Update the ball's velocity
    ball.SetVelocity(ballVelocity);
   
    SDL_RenderCopyEx(m_renderer, arrowTexture, &src, &dest, angle, &pivot, SDL_FLIP_NONE);
    SDL_DestroyTexture(arrowTexture);
   }

void RenderWindow::Clear()
{
	SDL_RenderClear(m_renderer);
}

void RenderWindow::Cleanup() 
{
    SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void RenderWindow::Display() 
{
	SDL_RenderPresent(m_renderer);
}


