#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Game.h"

int main(int argc, char* argv[]) 
{
    Game game;
    if (game.Init())
    {
        game.Run();
    }
    return 0;
}
