#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Player: public Character
{

    public:
        Player( Properties* props );

        virtual void Draw();
        virtual void Update( float dt );
        virtual void Clean();

    private:
        //int m_Row, m_Frame, m_FrameCount, m_AnimSpeed;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};

#endif // PLAYER_H
