#pragma once
#include <SDL.h> 
#include <SDL_image.h>

#include "../entity/Ball.h"

class RenderWindow
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	int m_width;
	int m_height;
public:
	RenderWindow(const char* title, int width, int height);
	SDL_Texture* LoadTexture(const char* filePath);
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	void Render(Ball& ball);
	void RenderArrow(Ball& ball, float angle);
	void Clear();
	void Cleanup();
	void Display();
};
