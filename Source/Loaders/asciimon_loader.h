#ifndef ASCIIMON_LOADER_H
#define ASCIIMON_LOADER_H

#include "b_loader.h"
#include "asciimon.h"
#include "asciimon_cache.h"

class Asciimon_Loader : public Loader_Base
{
    public:
        void load ( Asciimon* asciimon, unsigned id );

    private:
        void getType    ();

        void getImageFront  ();
        void getImageBack   ();

        void getLvlUpMoves  ();

    private:
        const std::string getFileName   () const override;

        Asciimon*       m_p_asciimon = nullptr;
        Asciimon_Cache  m_cache;

        unsigned m_idToLoad;
};

#endif // ASCIIMON_LOADER_H
