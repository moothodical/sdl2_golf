#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "util/Constants.h"
#include "entity/Ball.h"
#include "render/RenderWindow.h"

int main(int argc, char* argv[]) 
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    RenderWindow window = RenderWindow("Golf", WINDOW_WIDTH, WINDOW_HEIGHT);

    // ball
    SDL_Texture* ballTexture = window.LoadTexture("res/player.png");
    Ball ball(Vector2f(500, 500), 47, ballTexture);
    
    // Main loop flag
    bool quit = false;
    SDL_Event e;

        
    // delta time
    Uint64 last = SDL_GetPerformanceCounter();
    double deltaTime = 0;

    // Main loop
    while (!quit) 
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (now - last) / (double)SDL_GetPerformanceFrequency();
        last = now;

        while (SDL_PollEvent(&e) != 0) 
        {
            if (e.type == SDL_QUIT) 
            {
                quit = true;
            }
            ball.Input(e);
        }
        ball.Update(deltaTime);
        window.Clear();
        window.Render(ball);
        window.Display();
    }

    // Clean up
    window.Cleanup();
    SDL_Quit();

    return 0;
}
