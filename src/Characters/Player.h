#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_TIME 20.0f
#define JUMP_FORCE 10.0f

class Player: public Character
{

    public:
        Player( Properties* props );

        virtual void Draw();
        virtual void Update( float dt );
        virtual void Clean();

    private:
        bool m_IsJumping;
        bool m_IsGrounded;

        float m_JumpTime;
        float m_Jump_Force;

        Collider* m_Collider;

        Animation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;
};

#endif // PLAYER_H
