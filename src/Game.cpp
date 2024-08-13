#include "Game.h"

Game::Game()
	: m_window(RenderWindow("Golf", WINDOW_WIDTH, WINDOW_HEIGHT))
{

}

Game::~Game()
{
	CleanUp();
}

bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    LoadTextures();
    return true;
}

void Game::LoadTextures()
{
    SDL_Texture* bgTexture = m_window.LoadTexture("res/bg.png");

    // ball
    SDL_Texture* ballTexture = m_window.LoadTexture("res/player.png");
    Ball ball(Vector2f(100, 100), 15, ballTexture);
    
    m_textures["bg"] = bgTexture;
    m_textures["ball"] = ballTexture;
}

void Game::Run()
{
    #pragma region setup
    bool quit = false;
    SDL_Event e;

    // delta time
    Uint64 last = SDL_GetPerformanceCounter();
    double deltaTime = 0;
    #pragma endregion

    #pragma region object_creation
    Ball ball(Vector2f(100, 100), 15, m_textures["ball"]);
    #pragma endregion
    
    #pragma region main_loop
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
        m_window.Clear();
        m_window.Render(m_textures["bg"]);
        m_window.Render(ball);
        m_window.Display();
    }
    #pragma endregion
}

void Game::CleanUp()
{
    for (const auto& pair : m_textures)
    {
        SDL_DestroyTexture(pair.second);
    }
    m_textures.clear();
    
    SDL_Quit();
}