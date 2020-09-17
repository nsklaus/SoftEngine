#include <SDL2/SDL.h>
#include "Player.h"
#include "TextureManager.h"
#include "Input.h"

Player::Player( Properties* props ): Character(props)
{
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps( m_TextureID, 6, 1, 60 );
}

void Player::Draw()
{
    m_Animation->Draw( m_Transform->X, m_Transform->Y, m_Width, m_Height );
}

void Player::Update(float dt)
{
    // default animation (idle)
    m_Animation->SetProps( "samus", 6, 1, 60 );

    // reset applying force
    m_RigidBody->UnSetForce();

    if( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_LEFT ) )
    {
        // animation run to the right
        m_Animation->SetProps( "samus", 0, 10, 60 );
        // SDL_Log( " key Left pushed " );
        m_RigidBody->ApplyForceX( 5 * BACKWARD );
    }

    if( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_RIGHT ) )
    {
        // animation run to the left
        m_Animation->SetProps( "samus", 1, 10, 60 );
        // SDL_Log( " key Right pushed " );
        m_RigidBody->ApplyForceX( 5 * FORWARD );
    }

    // apply physics
    m_RigidBody->Update( dt );

    // apply position
    m_Transform->TranslateX( m_RigidBody->GetPosition().X );

    // apply grativy
    // m_Transform->TranslateY( m_RigidBody->GetPosition().Y );

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    m_Animation->Update();
}

void Player::Clean()
{
    TextureManager::GetInstance()->Clean();
}
