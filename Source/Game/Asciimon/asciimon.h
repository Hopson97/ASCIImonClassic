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

        void drawFront  () const;
        void drawBack   () const;
        const Image& getFrontImage  () const;
        const Image& getBackImage   () const;

        void printStats ();

        void setLevel   ( unsigned level );
        const unsigned getLevel     () const;

        const std::string& getName  () const;

    private:
        Asciimon_Data   m_stats;
        Level           m_level;

        std::string     m_name = " ";

        const Asciimon_Cache* m_asciimonCache = nullptr;

        std::vector<Asciimon_Move> m_moves;
};

#endif // ASCIIMON_H
