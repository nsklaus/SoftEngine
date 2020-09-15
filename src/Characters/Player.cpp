#include "Player.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>

Player::Player( Properties* props ): Character(props) {
//    m_Row = 0;
//    m_FrameCount = 6;
//    m_AnimSpeed = 80;
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps( m_TextureID, 0, 6, 80, SDL_FLIP_HORIZONTAL );
}

void Player::Draw() {
    //TextureManager::GetInstance()->DrawFrame( m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame );
    m_Animation->Draw( m_Transform->X, m_Transform->Y, m_Width, m_Height );
}

void Player::Update(float dt) {
    //m_Frame = ( SDL_GetTicks()/m_AnimSpeed ) % m_FrameCount;
    m_RigidBody->Update( 0.2 );
    m_RigidBody->ApplyForceX( 5 );

    // m_Transform->X += m_RigidBody->GetPosition().X;
    // m_Transform->Y += m_RigidBody->GetPosition().Y;
    // both methods (commented above and also below) should work the same
    // two ways of doing same thing
    m_Transform->TranslateX( m_RigidBody->GetPosition().X );
    m_Transform->TranslateY( m_RigidBody->GetPosition().Y );

    m_Animation->Update();
}

void Player::Clean() {
    TextureManager::GetInstance()->Clean();
}
