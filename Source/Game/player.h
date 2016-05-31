#ifndef PLAYER_H
#define PLAYER_H

#include "Maths/vector2.h"

class Player
{
    Vector2i m_mapLocation;
    Vector2i m_fieldLocation = { 5, 10 };


    public:
        Player();

        const Vector2i&
        getFieldLocation    () const;

        void
        moveInField         ( const Vector2i& amount );

    private:
};

#endif // PLAYER_H
