#include "asciimon_data.h"

Asciimon_Data :: Asciimon_Data ()
{
    stats[ Stat_Name::Hit_Points        ] = Asciimon_Stat();

    stats[ Stat_Name::Attack            ] = Asciimon_Stat();
    stats[ Stat_Name::Special_Attack    ] = Asciimon_Stat();

    stats[ Stat_Name::Defence           ] = Asciimon_Stat();
    stats[ Stat_Name::Special_Defence   ] = Asciimon_Stat();

    stats[ Stat_Name::Speed             ] = Asciimon_Stat();

}
