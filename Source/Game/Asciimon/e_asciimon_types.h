#ifndef D_ASCIIMON_TYPES_H_INCLUDED
#define D_ASCIIMON_TYPES_H_INCLUDED

#include "console_funcs.h"
#include "e_console_colours.h"
#include <map>

enum class Asciimon_Type
{
    Normal  = 0,
    Grass   = 1,
    Water   = 2,
    Fire    = 3,
    Bug     = 4
};

namespace Asciimon_Type_Colours
{

extern std::map<Asciimon_Type, Console::Foreground_Colour> convert;

}

#endif // D_ASCIIMON_TYPES_H_INCLUDED
