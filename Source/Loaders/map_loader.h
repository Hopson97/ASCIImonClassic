#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "../Game/Map/map.h"

#include "b_loader.h"


class Map_Loader : private Loader_Base
{
    public:
        Map_Loader      ();

        void load       ( Map* p_map );

    private:
        void readName               ();
        void readMapChars           ();
        void countPortalsOnLine     ();
        void countPeopleOnLine      ();
        void readPortal             ();
        void readPerson             ();

        void bindKeywords           () override;

        void readEncounterableAsciimon  ();
        const std::string getFileName   () const override;


        Map* m_p_map = nullptr;
};

#endif // MAP_LOADER_H
