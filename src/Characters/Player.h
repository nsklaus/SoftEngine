#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player: public Character {

    public:
        Player( Properties* props );

        virtual void Draw();
        virtual void Update( float dt );
        virtual void Clean();

    private:
        int m_Row, m_Frame, m_FrameCount, m_AnimSpeed;
};

#endif // PLAYER_H