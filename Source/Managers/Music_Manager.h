#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H


#include <string>

namespace Music_Manager
{
    void pushSong   ( const std::string& songName, unsigned volume = 25 );
    void popSong    ();
};

#endif // MUSIC_MANAGER_H
