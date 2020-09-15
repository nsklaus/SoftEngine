#include "Engine.h"
#include <iostream>
#include "TextureManager.h"
#include "Player.h"
//#include "Vector2D.h"

Engine* Engine::s_Instance = nullptr;
Player* samus = nullptr;

bool Engine::Init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 && IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) !=0 ){
        SDL_Log( "Failed to initialize video: %s",SDL_GetError() );
        return false;
    }

    m_Window = SDL_CreateWindow( "SSEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
    if( m_Window == nullptr ){
        SDL_Log( "Failed to create window: %s",SDL_GetError() );
        return false;
    }

    m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( m_Renderer == nullptr ){
        SDL_Log( "Failed to create renderer: %s",SDL_GetError() );
        return false;
    }
    TextureManager::GetInstance()->Load( "samus", "assets/entities/samus.png" );
    // 528x624
    samus = new Player( new Properties("samus", 50, 50, 48, 48));
//    Vector2D v1, v2;
//    v1.Log("v1 :");

    m_IsRunning = true;
    return true;
}


void Engine::Update()
{
    samus->Update(0);
    // SDL_Log("blib blob blub");
    // std::cout << "it's running" << std::endl;
}

void Engine::Render()
{
    SDL_SetRenderDrawColor( m_Renderer, 124, 218, 254, 255 );
    SDL_RenderClear( m_Renderer );
    //TextureManager::GetInstance()->Draw( "bleep", 100, 100, 90, 77 );
    samus->Draw();
    SDL_RenderPresent( m_Renderer );
}

void Engine::Events()
{
    SDL_Event event;
    SDL_PollEvent( &event );
    switch( event.type ){
        case SDL_QUIT:
            Quit();
            break;
    }
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
