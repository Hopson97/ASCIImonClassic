#include "d_tiles.h"

namespace Tiles
{

//Tiles the block the player
const std::vector<char> blocks =
{
    '#',
    '{',
    '+',
    '@',
    '-'
};

const std::vector <char> water =
{
    '~',
    '*'
};

const std::vector <char> encounterTiles =
{
    '|',
    ','
};


//Recognised tiles and their colours
const std::map<char, Console::Foreground_Colour> colours =
{
    { '@',  Console::Foreground_Colour::CYAN        },

    { '#',  Console::Foreground_Colour::DARKRED     },  //Common tiles, eg block, grass, sand etc
    { '.',  Console::Foreground_Colour::GREEN       },  //grass
    { '_',  Console::Foreground_Colour::WHITE       },  //flooring
    { '-',  Console::Foreground_Colour::GRAY        },  //Table
    { '\'', Console::Foreground_Colour::YELLOW      },  //No clue


    { '>',  Console::Foreground_Colour::MAGENTA     },  //Move tiles
    { '<',  Console::Foreground_Colour::MAGENTA     },  //Ones that move into new map
    { '^',  Console::Foreground_Colour::MAGENTA     },
    { 'v',  Console::Foreground_Colour::MAGENTA     },

    { '1',  Console::Foreground_Colour::YELLOW      },  //Portals
    { 'n',  Console::Foreground_Colour::YELLOW      },

    { ',', Console::Foreground_Colour::DARKGREEN    },  //Tall grass
    { '|', Console::Foreground_Colour::DARKGREEN    },

    { '+', Console::Foreground_Colour::RED          },  //"Health" sign

    { '{', Console::Foreground_Colour::GRAY         },  //Buildings/ walls

    { '~', Console::Foreground_Colour::BLUE         },  //Water
    { '*', Console::Foreground_Colour::DARKBLUE     }   //Water

};


//Tiles that when the player steps on, it loads a new area and the "direction" of them
const std::map<char, Vector2i> mapMoves =
{
    { '>',  {  1,  0 } },
    { '<',  { -1,  0 } },
    { '^',  {  0,  1 } },
    { 'v',  {  0, -1 } },
    { 'V',  {  0, -1 } }
};

//Portals eg doors, and the "direction" the player faces when entering through them
const std::map<char, Vector2i> portals
{
    { '1', { 1,  0 } },
    { 'n', { -1, 0 } }
};

}
