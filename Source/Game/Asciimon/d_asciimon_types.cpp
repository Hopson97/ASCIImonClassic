#include "e_asciimon_types.h"
#include "console_funcs.h"
#include "e_console_colours.h"
#include <map>

namespace Asciimon_Type_Colours
{

std::map<Asciimon_Type, Console::Foreground_Colour> convert =
{
    { Asciimon_Type::Normal,    Console::Foreground_Colour::WHITE },
    { Asciimon_Type::Grass,     Console::Foreground_Colour::GREEN },
    { Asciimon_Type::Water,     Console::Foreground_Colour::CYAN },
    { Asciimon_Type::Fire,      Console::Foreground_Colour::RED },
    { Asciimon_Type::Bug,       Console::Foreground_Colour::DARKGREEN },
};

}
