#ifndef WILD_ENCOUNTER_H
#define WILD_ENCOUNTER_H

#include "b_encounter.h"

namespace State
{

class Wild_Encounter : public Encounter_Base
{
    public:
        Wild_Encounter( Game_Main& game, unsigned enemyId, unsigned levelOfEnemy );

    private:
        void loadEnemy( unsigned enemyId, unsigned levelOfEnemy );
        void initEncounter() override;

        Asciimon m_asciimon;

};

}

#endif // WILD_ENCOUNTER_H
