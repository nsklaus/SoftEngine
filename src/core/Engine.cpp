#include "Engine.h"
#include <iostream>
#include "TextureManager.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"

Engine* Engine::s_Instance = nullptr;
Player* Samus = nullptr;

bool Engine::Init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 && IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) !=0 )
    {
        SDL_Log( "Failed to initialize video: %s",SDL_GetError() );
        return false;
    }


    SDL_WindowFlags wf = ( SDL_WindowFlags ) ( SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
    m_Window = SDL_CreateWindow( "SSEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, wf );
    if( m_Window == nullptr )
    {
        SDL_Log( "Failed to create window: %s",SDL_GetError() );
        return false;
    }

    m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( m_Renderer == nullptr )
    {
        SDL_Log( "Failed to create renderer: %s",SDL_GetError() );
        return false;
    }

    if(!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("map0001");


    TextureManager::GetInstance()->Load( "samus", "assets/entities/samus.png" );
    // tilesheet res: 528x624, tile res: 48x48
    Samus = new Player( new Properties("samus", 50, 50, 48, 48));

    m_IsRunning = true;
    return true;
}


void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    Samus->Update( dt );
}

void Engine::Render()
{
    SDL_SetRenderDrawColor( m_Renderer, 124, 218, 254, 255 );
    SDL_RenderClear( m_Renderer );
    m_LevelMap->Render();
    Samus->Draw();
    SDL_RenderPresent( m_Renderer );
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer( m_Renderer );
    SDL_DestroyWindow( m_Window );
    IMG_Quit();
    SDL_Quit();
    return true;
}

void Engine::Quit()
{
    m_IsRunning = false;
}
