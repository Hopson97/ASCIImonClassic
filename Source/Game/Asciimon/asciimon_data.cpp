#include "asciimon_data.h"

Asciimon_Data :: Asciimon_Data ()
{
    //Filling up the map
    m_stats[ Stat_Name::Hit_Points        ] = Asciimon_Stat();

    m_stats[ Stat_Name::Attack            ] = Asciimon_Stat();
    m_stats[ Stat_Name::Special_Attack    ] = Asciimon_Stat();

    m_stats[ Stat_Name::Defence           ] = Asciimon_Stat();
    m_stats[ Stat_Name::Special_Defence   ] = Asciimon_Stat();

    m_stats[ Stat_Name::Speed             ] = Asciimon_Stat();

}

void Asciimon_Data :: levelUp ( const Asciimon_Cache& cache )
{
    m_stats[ Stat_Name::Hit_Points        ].levelUp( 1, cache.getBaseIncreases().hitpoints );

    m_stats[ Stat_Name::Attack            ].levelUp( 1, cache.getBaseIncreases().attack );
    m_stats[ Stat_Name::Special_Attack    ].levelUp( 1, cache.getBaseIncreases().spAttack );

    m_stats[ Stat_Name::Defence           ].levelUp( 1, cache.getBaseIncreases().defence );
    m_stats[ Stat_Name::Special_Defence   ].levelUp( 1, cache.getBaseIncreases().spDefence );

    m_stats[ Stat_Name::Speed             ].levelUp( 1, cache.getBaseIncreases().speed );
}

void Asciimon_Data ::fullRestore ()
{
    for ( auto& stat : m_stats )
    {
        stat.second.reset();
    }
}

const std::map< Stat_Name, Asciimon_Stat >& Asciimon_Data :: getStats () const
{
    return m_stats;
}

void Asciimon_Data :: deductStat ( Stat_Name name, unsigned amount )
{
    m_stats.at( name ).deduct( amount );


}
