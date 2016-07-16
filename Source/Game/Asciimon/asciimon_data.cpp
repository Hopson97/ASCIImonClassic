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
    //m_stats.at()
}

const std::map< Stat_Name, Asciimon_Stat >& Asciimon_Data :: getStats () const
{
    return m_stats;
}
