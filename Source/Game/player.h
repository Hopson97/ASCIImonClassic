#ifndef PLAYER_H
#define PLAYER_H

#include "Maths/vector2.h"
#include "asciimon.h"

#include <vector>

class Player
{
    public:
        Player();

        const Vector2i& getFieldLocation    () const;

        void moveInField         ( const Vector2i& amount );
        void setFieldPosition    ( const Vector2i& location );

        Asciimon& getFrontAsciimon ();

        void setName ( const std::string& name );

    private:
        struct Field_Variables
        {
            Vector2i location = { 11, 13 };
            Vector2i direction;
        } m_fieldData;

        std::vector<Asciimon> m_asciimon;
        std::string m_name;

};

#endif // PLAYER_H
