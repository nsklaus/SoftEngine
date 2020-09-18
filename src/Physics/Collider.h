#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL2/SDL.h"
#include "Engine.h"
#include "Camera.h"
#include "Vector2D.h"

//using Box = SDL_Rect;  "Box m_Box;" is equal to: "SDL_Rect m_Box;"

class Collider
{
    public:
        inline SDL_Rect Get(){ return m_Box; }
        inline void SetBuffer( int x, int y, int w, int h ) { m_Buffer = { x, y, w, h }; }
        void DrawDebug()
        {
            Vector2D cam = Camera::GetInstance()->GetPosition();
            m_Box.x -= cam.X;
            m_Box.y -= cam.Y;
            SDL_RenderDrawRect( Engine::GetInstance()->GetRenderer(), &m_Box);
        }

        void Set( int x, int y, int w, int h )
        {
            m_Box = {
                x - m_Buffer.x,
                y - m_Buffer.y,
                w - m_Buffer.w,
                h - m_Buffer.h,
            };
        }

    private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};

#endif // COLLIDER_H
