#include "States/roaming.h"

#include "../Utilities/random_functions.h"

#include "game_funcs.h"
#include "Map/d_tiles.h"
#include "wild_encounter.h"

//This file is the encounter generator, for when you might find a wild Asciimon or Trainer while roaming around
//This will check the map Asciimon data and get the ID of a Asciimon to fight
namespace State
{

void Roaming :: testForWildEncounter ()
{
    if ( !testForWildEncounterTile() ) return;

    constexpr static unsigned annoyenceReductionMultiplier = 7;  //Lessens the chance of an encounter by increasing
                                                            //the "chance bounds" thus reducing the "asciimon bounds"
    unsigned total = m_map.getTotalAsciimonWeight();
    unsigned chance = Random::integer( 0, total * annoyenceReductionMultiplier );

    if ( chance > total - 1 ) return;
    else
        startWildEncounter( chance );
}


//Checks if the tile being stood on is a tile that has potential to have an encounter eg long grass
bool Roaming :: testForWildEncounterTile ()
{
    for ( auto& tile : Tiles::encounterTiles )
    {
        if ( tile == getTileAtPlayerCurrLocation() )
            return true;
    }
    return false;
}


#define FAILURE 0

void Roaming :: startWildEncounter ( const unsigned chance )
{
    unsigned level;
    unsigned id = getWildAsciimonIdToEncounter( chance, level );

    if ( id == FAILURE ) return;


    getGame().getStates().pushState( new State::Wild_Encounter( getGame(), id, level ) );

}


/*  Gets the ASCIImon ID of the ASCIImon to encounter, which takes two steps:
 *  Step One:
 *       We need to get the bounds of the map's encounterable ASCIImons' weights, and create
 *       a lower/ upper bound structure.
 *       Eg: let AM = an arbitary Asciimon, followed by their index and then "weight/chance"
 *       AM1 0->15 | AM2 16-20 | AM3 21-30
 *       If the chance is 17, then AM2 will be encountered
 *
 *       The ranges are based off their weights, which is added onto the previous total
 *
 *
 *       With the "chance" somewhere between those bounds, and each bound has an attached id with it
 *       as seen in the struct above.
 *
 *   Step Two:
 *       The bounds are simply checked against the bounds until the correct ASCIImon is found
 */
unsigned Roaming :: getWildAsciimonIdToEncounter ( const unsigned chance, unsigned& level )
{
    struct Potential_ASCIImon
    {
        unsigned lowerBound;
        unsigned upperBound;
        unsigned id;
        unsigned level;
    };
    std::vector<Potential_ASCIImon> potentialAsciimon;

    //Step One:
    unsigned total = 0;
    for ( auto& asciimon : m_map.getEncounterableAsciimon() )
    {
        potentialAsciimon.push_back( {  total,
                                        total + asciimon.getWeight() - 1,
                                        asciimon.getId(),
                                        (unsigned)Random::integer( asciimon.getLowLevel(), asciimon.getHighLevel()  )
                                      } );
        total += asciimon.getWeight();
    }

    //Step Two:
    for ( auto& asciimon : potentialAsciimon )
    {
        if ( asciimon.lowerBound <= chance &&
            asciimon.upperBound >= chance )
        {
            level = asciimon.level;
            return asciimon.id + 1;
        }
    }
    return FAILURE; //If this messes up somehow, then it returns an error number.
}

#undef FAILURE

}
