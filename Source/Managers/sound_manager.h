#ifndef SOUND_MANAGER_H_INCLUDED
#define SOUND_MANAGER_H_INCLUDED

#include <SFML/Audio.hpp>
#include <map>


namespace Sound_Manager
{

const sf::SoundBuffer& getSound (const std::string& name);

}



#endif
