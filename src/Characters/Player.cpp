#include "Player.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>

Player::Player( Properties* props ): Character(props) {
    m_Row = 0;
    m_FrameCount = 6;
    m_AnimSpeed = 80;
}

void Player::Draw() {
    TextureManager::GetInstance()->DrawFrame( m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame );
}

void Player::Update(float dt) {
    m_Frame = ( SDL_GetTicks()/m_AnimSpeed ) % m_FrameCount;
}

void Player::Clean() {
    TextureManager::GetInstance()->Clean();
}
