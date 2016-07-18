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

        void moveInField        ( const Vector2i& amount );
        void setFieldPosition   ( const Vector2i& location );
        const Vector2i&  getDirection   ();

        Asciimon& getFrontAsciimon ();

        void setName ( const std::string& name );

        void give       ( const Asciimon& asciimon );

        void healAll    ();

    private:
        struct Field_Variables
        {
            Vector2i location = { 4, 2 };
            Vector2i direction;
        } m_fieldData;

        std::vector<Asciimon> m_asciimon;
        std::string m_name;

};

#endif // PLAYER_H
