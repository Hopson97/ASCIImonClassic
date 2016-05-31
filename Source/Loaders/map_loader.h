#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "map.h"

#include "b_loader.h"

class Map_Loader : private Loader_Base
{
    Map* m_p_map = nullptr;

    public:
        void
        load            ( Map* p_map );

    private:
        void
        checkLine       () override;

        void
        readMapChars    ();

        const std::string
        getFileName  () const override;

};

#endif // MAP_LOADER_H
