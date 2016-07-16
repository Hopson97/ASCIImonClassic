#ifndef ASCIIMON_MOVE_H
#define ASCIIMON_MOVE_H

#include "asciimon_move_cache.h"

class Asciimon_Move
{
    friend class Move_Loader;

    public:
        Asciimon_Move();

    private:
        const Asciimon_Move_Cache* m_info;

        unsigned m_movesLeft;
};

struct Level_Up_Move
{
    int level;
    std::string name;
};

#endif // ASCIIMON_MOVE_H
