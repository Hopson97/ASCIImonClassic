#ifndef MOVE_LOADER_H
#define MOVE_LOADER_H

#include "asciimon_move_cache.h"
#include "asciimon_move.h"
#include "b_loader.h"
#include "asciimon_move_cache.h"

class Move_Loader : public Loader_Base
{
    public:
        void load ( Asciimon_Move* move, const std::string& name );

    private:
        const std::string getFileName () const override;

        void getType ();

        Asciimon_Move_Cache m_cache;
        Asciimon_Move*      m_p_move;
        std::string         m_name;
};

#endif // MOVE_LOADER_H
