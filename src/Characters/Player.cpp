#include <SDL2/SDL.h>
#include "Player.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"

Player::Player( Properties* props ): Character(props)
{
    m_JumpTime = JUMP_TIME;
    m_Jump_Force = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer( -10, 0, 20, 0 );

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity( 3.0f );

    m_Animation = new Animation();
    m_Animation->SetProps( m_TextureID, 6, 1, 60 );
}

void Player::Draw()
{
    m_Animation->Draw( m_Transform->X, m_Transform->Y, m_Width, m_Height );
    m_Collider->DrawDebug();
}

void Player::Update(float dt)
{
    m_Animation->SetProps( "samus", 6, 1, 60 ); // default animation (idle)
    m_RigidBody->UnSetForce();

    if( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_LEFT ) )
    {
        m_RigidBody->ApplyForceX( 5 * BACKWARD );
        m_Animation->SetProps( "samus", 0, 10, 60 ); // animation left
    }

    if( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_RIGHT ) )
    {
        m_RigidBody->ApplyForceX( 5 * FORWARD );
        m_Animation->SetProps( "samus", 1, 10, 60 ); // animation right
    }

    // jumping
    if ( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_W ) && m_IsGrounded )
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY( UPWARD*m_Jump_Force );
    }
    if ( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_W ) && m_IsJumping && m_JumpTime > 0 )
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY( UPWARD*m_Jump_Force );
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    //move on X axis
    m_RigidBody->Update( dt ); // apply physics
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->GetPosition().X;
    m_Collider->Set( m_Transform->X, m_Transform->Y, 48, 48 );
    if ( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
        m_Transform->X = m_LastSafePosition.X;

    //move on Y axis
    m_RigidBody->Update( dt ); // apply physics
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->GetPosition().Y;
    m_Collider->Set( m_Transform->X, m_Transform->Y, 48, 48 );
    if ( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else
    {
        m_IsGrounded = false;
    }

    // apply position
    //m_Transform->TranslateX( m_RigidBody->GetPosition().X );

    // apply grativy
    // m_Transform->TranslateY( m_RigidBody->GetPosition().Y );

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    m_Animation->Update();
}

void Player::Clean()
{
    TextureManager::GetInstance()->Drop( m_TextureID );
}
