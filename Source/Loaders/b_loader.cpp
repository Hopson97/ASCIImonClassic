#include "b_loader.h"

#include <stdexcept>

void
Loader_Base :: addKeyword ( std::function<void(void)> function, const std::string& keyword)
{
    m_keywords[keyword] = function;
}

//Fully reads the file, using the functions and keyword pairs passed in from a derived class
void
Loader_Base :: readFile ( const std::string& fileType )
{
    prepareForLoad();
    openFile( fileType, getFileName() );

    while ( readLine() )
    {
        if ( checkForWord( "//" ) ) continue;
        checkLineForKeyword();
    }
    m_inFile.close();
}

//Goes through the function/ keyword list and calls a function if the keyword matches the read line
//If it does not, it means an unrecognised word is found, of which needs to be dealt with
void
Loader_Base :: checkLineForKeyword ()
{
    for ( auto& keyword : m_keywords )
    {
        if ( checkForWord( keyword.first ) )
        {
            keyword.second();
            return;
        }
    }
    throwUnrecognisedWord();
}


const std::string&
Loader_Base :: getCurrentLineString () const
{
    return m_line;
}

//Bunch of reader functions for the derived classes
bool
Loader_Base :: readLine ()
{
    return std::getline( m_inFile, m_line );
}

void
Loader_Base :: readNumber ( int& number )
{
    m_inFile >> number;
}

void
Loader_Base :: readVector2i ( Vector2i& vector )
{
    m_inFile >> vector.x >> vector.y;
}

bool
Loader_Base :: checkForWord ( const std::string& wordToCheckFor ) const
{
    return m_line.find ( wordToCheckFor ) != std::string::npos;
}


void
Loader_Base :: throwUnrecognisedWord   () const
{
    if ( m_line == "") return;
    throw std::runtime_error ( "\tFound unknown word: " +
                                m_line +
                               ", terminating program.\
                               \n");
}

//Each section of the files is marked by a END, and this checks for that
bool
Loader_Base :: endOfSection ()
{
    readLine();
    return checkForWord( "END" );
}



void
Loader_Base :: openFile ( const std::string& type, const std::string& path )
{
    m_inFile.open ( path );

    if ( !m_inFile.is_open() ) {
        throw std::runtime_error ( "File type of type \"" + type +
                                  "\" at \"" + path +
                                  "\" does not exist.");
    }
}


//: ^ )
void
Loader_Base :: prepareForLoad ()
{
    m_inFile.clear();
    m_line.clear();
}
