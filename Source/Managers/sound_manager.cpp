#include "sound_manager.h"

std::map<std::string, sf::SoundBuffer> m_sounds;

static void loadSound( const std::string& name )
{
    m_sounds[name] = sf::SoundBuffer();
	if ( !m_sounds[name].loadFromFile( "Data/Sounds/" + name + ".ogg" ) )
	{
		throw std::runtime_error ( "Could not load sound at " + name );
	}
}

const sf::SoundBuffer & Sound_Manager :: getSound(const std::string& name)
{
    if ( !m_sounds.count( name ) ) loadSound( name );
	return m_sounds.at( name );
}

