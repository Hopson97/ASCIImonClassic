#include "Music_Manager.h"

#include <stack>

#include <SFML/Audio.hpp>
#include <memory>


namespace Music_Manager
{

std::stack<std::unique_ptr<sf::Music>> m_music;

void pushSong   ( const std::string& songName, unsigned volume )
{
    if ( !m_music.empty() )
    {
        m_music.top()->stop();
    }

    m_music.push( std::make_unique<sf::Music>() );
    m_music.top()->openFromFile( "Data/Music/" + songName  + ".ogg" );
    m_music.top()->setVolume ( volume );
    m_music.top()->play();
}



void popSong    ()
{
    if ( !m_music.empty() )
    {
        m_music.top()->stop();
        m_music.pop();
        m_music.top()->play();
    }
}

}
