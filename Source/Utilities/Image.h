#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <fstream>

#include "e_console_colours.h"
#include "console_funcs.h"


class Image
{
    public:
        Image   () = default;

        Image   ( const std::string& fileName );
        Image   ( std::ifstream& inFile );

        void loadFromFile   ( const std::string& fileName );
        void loadFromStream ( std::ifstream& inFile );

        void draw           () const;
        void setColour      ( Console::Foreground_Colour colour  );

    private:
        std::string path = "Data/Images/";
        std::string extention = ".ascimg";

        std::string m_image;

        Console::Foreground_Colour m_colour = Console::Foreground_Colour::WHITE;
};

#endif // IMAGE_H
