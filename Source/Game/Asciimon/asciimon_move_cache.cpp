#include "asciimon_move_cache.h"

#include <map>

std::map<std::string, Asciimon_Move_Cache> mainMoveCache;

bool Asciimon_Move_Cache :: moveExists ( const std::string& name )
{
    return mainMoveCache.count( name );
}

void Asciimon_Move_Cache :: addMove ( const std::string& name, const Asciimon_Move_Cache& cache )
{
    mainMoveCache[name ] = cache;
}

Asciimon_Move_Cache& Asciimon_Move_Cache :: getMove ( const std::string& name )
{
    try
    {
        return mainMoveCache.at( name );
    }
    catch ( std::out_of_range e )
    {
        throw std::runtime_error ( "Move " + name + " does not exist!" );
    }
}

const Asciimon_Move_Cache::Info& Asciimon_Move_Cache :: getInfo() const
{
    return m_info;
}
