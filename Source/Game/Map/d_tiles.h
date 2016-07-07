#ifndef D_TILES_H_INCLUDED
#define D_TILES_H_INCLUDED

#include <vector>
#include <map>

#include "../../Utilities/console_funcs.h"
#include "../Maths/vector2.h"

namespace Tiles
{

const extern std::vector <char> blocks;

const extern std::vector <char> water;

const extern
std::vector <char> encounterTiles;

const extern std::map <char, Console::Foreground_Colour > colours;

const extern std::map <char, Vector2i> mapMoves;

const extern std::map <char, Vector2i> portals;
}

#endif // D_TILES_H_INCLUDED
