#include "talk_scene.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "general_funcs.h"
#include "game_funcs.h"

Talk_Scene::Talk_Scene()
{

}


Talk_Scene::Talk_Scene ( const std::string& file, const Image& image )
:   m_animText ( image )
,   m_fileName ( file )
{
   readFile( file );
}

void Talk_Scene :: begin()
{
    for ( auto& line : m_lines )
    {
        m_animText.setText( constructString( line ) );
        m_animText.display();
    }
}

void Talk_Scene :: readFile ( const std::string& fileName )
{
    std::ifstream inFile;
    General::openFile( "Data/Talking/" + fileName + ".talk" , inFile );

    std::string line;
    while ( std::getline( inFile, line ) )
    {
        if ( line.length() == 0 ) continue;

        if ( General::lineContains( line, "$var " ) )
        {
            //The "talk files" can contain variables. This will get the variable name and add it to a couple
            //data structures

            //4 is the length (in char) of "var " in the file
            std::string var = line.substr( 4, line.length() - 4 );

            m_variables[var] = "";
            continue;
        }
        m_lines.push_back( line );
    }
}

void Talk_Scene :: setVar ( const std::string& varName, const std::string& replaceWith )
{
    m_variables[varName] = replaceWith;
}

std::string Talk_Scene :: constructString ( const std::string& line ) const
{
    std::string finalString = line;
    bool varFound = false;

    loopThroughString( finalString, varFound );

    return finalString;
}

void Talk_Scene :: loopThroughString ( std::string& finalString, bool& varFound ) const
{
    while ( true )
    {
        varFound = false;
        //Loops for the string, checking each char for the variable specifier and then replaces the variable with the contents of it
        for ( size_t i = 0 ; i < finalString.length() - 1 ; i++ )
        {
            checkCharForVar( finalString, varFound, i );
            if ( varFound ) break;
        }

        if ( varFound )
            continue;
        else
            break;
    }
}

void Talk_Scene :: checkCharForVar ( std::string& finalString, bool& varFound, const int i ) const
{
    if ( finalString.at( i ) == '$' ) // "$" is the variable specifier
    {
        std::string temp = finalString.substr( i + 1, finalString.length() );
        for ( auto& var : m_variables )
        {
            //eg "My name is $name, hello." becomes "name, hello" and this will check for "name" aka var.first
            if (General::lineContains( temp.substr( 0, var.first.length() ), var.first ) )
            {
                finalString.replace ( i, var.first.length() + 1, var.second );
                varFound = true;
            }
            if ( varFound )
                return;
        }
    }
}
