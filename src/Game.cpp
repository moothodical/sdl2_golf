#include "Game.h"

Game::Game()
	: m_window(RenderWindow("Golf", WINDOW_WIDTH, WINDOW_HEIGHT)),
    m_grid(Grid(32)),
    m_font(nullptr),
    m_gameState(Game::GameState::PLAY),
    m_levelManager(LevelManager())
{
}

Game::~Game()
{
	CleanUp();
}

bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Could not initialize SDL_mixer! SDL_Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    TTF_Init();
    m_font = TTF_OpenFont("res/font.ttf", 25);
    LoadTextures();
    m_levelManager.Init(m_textures);
    InitObjects();
    return true;
}

void Game::InitObjects()
{
}

void Game::LoadTextures()
{
    SDL_Surface* gameStateSurface = TTF_RenderText_Solid(m_font, "game state:", { 255, 255, 255 });
    m_surfaces["gamestate"] = gameStateSurface;
    SDL_Texture* gameStateTexture = SDL_CreateTextureFromSurface(m_window.GetRenderer(), gameStateSurface);
    SDL_Texture* bgTexture = m_window.LoadTexture("res/bg.png");
    SDL_Texture* ballTexture = m_window.LoadTexture("res/player.png");
    SDL_Texture* wallTexture = m_window.LoadTexture("res/wall.png");
    SDL_Texture* holeTexture = m_window.LoadTexture("res/hole.png");
    
    m_textures["gamestate"] = gameStateTexture;
    m_textures["bg"] = bgTexture;
    m_textures["ball"] = ballTexture;
    m_textures["wall"] = wallTexture;
    m_textures["hole"] = holeTexture;
}

void Game::Input(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_RIGHT)
        {
            if (m_gameState == GameState::PLAY)
            {
                SetGameState(Game::GameState::LEVEL_EDIT);
            } 
            else if (m_gameState == GameState::LEVEL_EDIT)
            {
                SetGameState(Game::GameState::PLAY);
            }
        }
    }
}

void Game::Run()
{
    #pragma region setup
    bool quit = false;
    SDL_Event e;
    Level level = m_levelManager.GetCurrentLevel();
    // delta time
    Uint64 last = SDL_GetPerformanceCounter();
    double deltaTime = 0;

    #pragma endregion

    #pragma region object_creation
    Ball ball(Vector2f(level.m_ballLoc), 10, m_textures["ball"]);
    #pragma endregion

    UpdateGameStateText();
    
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

            Input(e);

            if (m_gameState == GameState::PLAY)
            {
				ball.Input(e);
            }
        }
		 
        // TODO: fix order
        ball.Update(deltaTime);
        m_window.Clear();
        m_window.Render(m_textures["bg"]);

        if (ball.CheckHoleCollision(level.m_hole))
        {
           level = m_levelManager.LoadNextLevel();
           ball.StopAndPlace(m_levelManager.GetCurrentLevel().m_ballLoc);
        }

        m_window.Render(m_grid);
        
        for (Wall& wall : level.m_walls)
		{
			m_window.Render(wall);
		}

        m_window.Render(level.m_hole);
        ball.CheckWallCollision(level.m_walls);
        m_window.Render(ball);

        // font stuff
        m_window.RenderGameStateText(m_textures["gamestate"], m_textures["gamestate_value"]);

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

    for (const auto& pair : m_surfaces)
    {
        SDL_FreeSurface(pair.second);
    }

    m_textures.clear();
    m_surfaces.clear();
    
    SoundManager::GetInstance()->Cleanup();
    TTF_Quit();
    SDL_Quit();
}

void Game::SetGameState(Game::GameState gameState)
{
    m_gameState = gameState;
    UpdateGameStateText();
    if (m_gameState == GameState::LEVEL_EDIT)
    {
        LevelEditor levelEditor = LevelEditor();
        levelEditor.Update();
    }
}

const char* Game::GetGameStateText()
{
    switch (m_gameState)
    {
		case GameState::PLAY:
			return "play";
		case GameState::LEVEL_EDIT:
			return "level editor";
    }
}

void Game::UpdateGameStateText()
{
    if (m_textures["gamestate_value"] != nullptr)
    {
		SDL_DestroyTexture(m_textures["gamestate_value"]);
    }

	SDL_FreeSurface(m_surfaces["gamestate_value"]);
    const char* text = GetGameStateText();
    SDL_Surface* gameStateValueSurface = TTF_RenderText_Solid(m_font, text, {255, 255, 255});
    m_surfaces["gamestate_value"] = gameStateValueSurface;
    SDL_Texture* gameStateValueTexture = SDL_CreateTextureFromSurface(m_window.GetRenderer(), gameStateValueSurface);
    m_textures["gamestate_value"] = gameStateValueTexture;

}