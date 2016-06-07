#ifndef PLAYER_H
#define PLAYER_H

#include "Maths/vector2.h"

class Player
{
    struct Field_Variables
    {
        Vector2i location = { 11, 13 };
        Vector2i direction;
    } m_fieldData;

    public:
        Player();

        const Vector2i&
        getFieldLocation    () const;

        void
        moveInField         ( const Vector2i& amount );

        void
        setFieldPosition    ( const Vector2i& location );

    private:
};

#endif // PLAYER_H
