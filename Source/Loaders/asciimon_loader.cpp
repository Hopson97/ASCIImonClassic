#include "asciimon_loader.h"

#include "../Utilities/t_casts.h"
#include "asciimon_cache.h"
#include "game_funcs.h"
#include "d_stat_names.h"
#include "t_casts.h"
#include "asciimon_move_cache.h"
#include "move_loader.h"

#include <iostream>

const std::string fileType              =   "Asciimon File (.asc)";
const std::string mapLocation           =   "Data/Asciimon/Monsters/";

const std::string nameSection           =   "NAME";
const std::string typeSection           =   "TYPE";

const std::string frontSection          =   "FRONT";
const std::string backSection           =   "BACK";

const std::string asciipediaSection     =   "ASCIIPEDIA";

const std::string lvlUpMoveSection      =   "MOVES LVL";


void Asciimon_Loader :: load ( Asciimon* asciimon, unsigned id )
{
    m_idToLoad = id;
    m_p_asciimon = asciimon;

    m_cache = Asciimon_Cache();

    if ( !Asciimon_Cache::idExists( id ) )
    {
        addKeyword( std::bind ( &Asciimon_Loader::getType,          this ), typeSection );
        addKeyword( std::bind ( &Asciimon_Loader::getImageFront,    this ), frontSection );
        addKeyword( std::bind ( &Asciimon_Loader::getImageBack,     this ), backSection );
        addKeyword( std::bind ( &Asciimon_Loader::getLvlUpMoves,    this ), lvlUpMoveSection );

        addKeyword( m_cache.m_baseStats.attack,     Stat_Name_S::Abbreviated::attack );
        addKeyword( m_cache.m_baseStats.spAttack,   Stat_Name_S::Abbreviated::spAttack );

        addKeyword( m_cache.m_baseStats.defence,    Stat_Name_S::Abbreviated::defence );
        addKeyword( m_cache.m_baseStats.spDefence,  Stat_Name_S::Abbreviated::spDefence );

        addKeyword( m_cache.m_baseStats.hitpoints,  Stat_Name_S::Abbreviated::hitpoints );
        addKeyword( m_cache.m_baseStats.speed,      Stat_Name_S::Abbreviated::speed );

        addKeyword( &m_cache.m_name, nameSection );

        readFile( fileType );

        Asciimon_Cache::addAsciimonId( id, m_cache );
    }
    //Shorthand
    auto& cache = Asciimon_Cache::getAsciimon( id );
    m_p_asciimon->m_asciimonCache = &cache;

    Asciimon_Data& data = m_p_asciimon->m_stats;

    data.stats.at( Stat_Name::Attack )          = Asciimon_Stat( cache.getBaseStats().attack );
    data.stats.at( Stat_Name::Defence )         = Asciimon_Stat( cache.getBaseStats().defence );
    data.stats.at( Stat_Name::Special_Attack )  = Asciimon_Stat( cache.getBaseStats().spAttack );
    data.stats.at( Stat_Name::Special_Defence ) = Asciimon_Stat( cache.getBaseStats().spDefence );
    data.stats.at( Stat_Name::Speed )           = Asciimon_Stat( cache.getBaseStats().speed );
    data.stats.at( Stat_Name::Hit_Points )      = Asciimon_Stat( cache.getBaseStats().hitpoints );
}


const std::string Asciimon_Loader :: getFileName   () const
{
    return mapLocation + Convert::toString(m_idToLoad) + ".asc";
}


void Asciimon_Loader :: getType()
{
    int type;
    Loader_Base::readNumber( type );

    m_cache.m_type = static_cast<Asciimon_Type>( type );
}


void Asciimon_Loader :: getImageFront()
{
    Loader_Base::readImage( m_cache.m_frontImage );
}


void Asciimon_Loader :: getImageBack()
{
    Loader_Base::readImage( m_cache.m_backImage );
}


void Asciimon_Loader :: getLvlUpMoves ()
{
    const static std::string moveSection = "Move";
    const static std::string lvlSection = "LVL";

    Move_Loader moveLoader;

    while ( !Loader_Base::endOfSection() )
    {
        if ( Loader_Base::checkForWord( moveSection ) )
        {
            Level_Up_Move move;
            Loader_Base::readLine();

            for ( int i = 0 ; i < 2 ; i++ )
            {
                if ( checkForWord( nameSection ) )
                {
                    Loader_Base::readLine();
                    move.name = getCurrentLineString();
                    Loader_Base::readLine();
                    continue;
                }
                else if ( checkForWord( lvlSection ) )
                {
                    Loader_Base::readLine();
                    move.level = Convert::toNumber<unsigned>( getCurrentLineString() );
                    Loader_Base::readLine();
                    continue;
                }
                throwUnrecognisedWord();
            }
            Asciimon_Move realMove;
            moveLoader.load( &realMove, move.name );
            m_cache.m_levelUpMoves.push_back( move );
        }

    }
}
