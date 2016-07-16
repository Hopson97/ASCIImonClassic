#ifndef ASCIIMON_DATA_H_INCLUDED
#define ASCIIMON_DATA_H_INCLUDED

#include "Asciimon/asciimon_stat.h"
#include "e_stat_names.h"

#include <map>


struct Asciimon_Data
{
    Asciimon_Data();

    std::map< Stat_Name, Asciimon_Stat > stats;
};


#endif // ASCIIMON_DATA_H_INCLUDED
