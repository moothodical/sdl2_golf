#pragma once
#include <SDL.h> 
#include <SDL_image.h>

#include "../entity/Ball.h"
#include "../entity/Wall.h"
#include "../entity/Hole.h"
#include "../Grid.h"

class RenderWindow
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	int m_width;
	int m_height;
public:
	RenderWindow(const char* title, int width, int height);
	SDL_Renderer* GetRenderer() { return m_renderer; }
	SDL_Texture* LoadTexture(const char* filePath);
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	void Render(Ball& ball);
	void RenderArrow(Ball& ball, float angle);
	void Render(Wall& ball);
	void Render(Hole& hole);
	void Render(Grid& grid);
	void Render(SDL_Texture* texture);
	SDL_Rect GetTextRect(Vector2f position, SDL_Texture* texture);
	void RenderGameStateText(SDL_Texture* label, SDL_Texture* value);
	void Clear();
	void Cleanup();
	void Display();
};
