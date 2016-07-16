#ifndef ASCIIMON_H
#define ASCIIMON_H

#include <vector>

#include "asciimon_data.h"
#include "level.h"
#include "asciimon_move.h"

#include "asciimon_cache.h"

class Asciimon
{
    friend class Asciimon_Loader;

    public:
        Asciimon() = default;

        const Asciimon_Data& getStats () const;

        const Asciimon_Stat getStat   ( Stat_Name name ) const;

        void drawFront  () const;
        void drawBack   () const;
        const Image& getFrontImage  () const;
        const Image& getBackImage   () const;

        void printStats () const;

        void setLevel   ( unsigned level );
        const Level& getLevel   () const;

        const std::string& getName          () const;

        const std::vector<Asciimon_Move>& getMoves () const;

    private:
        void addMove ( const std::string& name );

        Asciimon_Data   m_stats;
        Level           m_level;

        std::string     m_name = " ";

        const Asciimon_Cache* m_asciimonCache = nullptr;

        std::vector<Asciimon_Move> m_moves;
};

#endif // ASCIIMON_H
