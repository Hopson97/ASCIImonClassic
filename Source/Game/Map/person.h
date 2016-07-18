#ifndef PERSON_H
#define PERSON_H

#include "../Maths/vector2.h"
#include <string>
#include <memory>

#include "talk_scene.h"
#include "player.h"

enum class Person_Type
{
    Regular = 0,
    Nurse = 1
};

class Person
{
    public:
        Person          ( const Vector2i& location );

        void setUp      ( const std::string& talkFile, const Image& image, Person_Type type = Person_Type::Regular );

        void interact   ( Player& player );

        const Vector2i& getLocation () const;


    private:
        Talk_Scene  m_talkScene;
        std::string name;
        Vector2i m_location;
        Person_Type m_type;
        Image m_image;
};

#endif // PERSON_H
