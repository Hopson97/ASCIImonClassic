#include "person.h"

Person :: Person( const Vector2i& location )
:   m_location ( location )
{
    //ctor
}

void Person :: setUp (  const std::string& talkFile, const Image& image, Person_Type type )
{
    m_image = image;
    m_talkScene = Talk_Scene( talkFile, m_image);
    m_type = type;
}

void Person::interact(Player& player)
{
    m_talkScene.begin();

    if ( m_type == Person_Type::Nurse )
    {
        player.healAll();
    }
}

const Vector2i& Person::getLocation() const
{
    return m_location;
}
