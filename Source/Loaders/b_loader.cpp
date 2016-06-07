#include "b_loader.h"

#include <stdexcept>

void
Loader_Base :: readFile ( const std::string& fileType )
{
    prepareForLoad();
    openFile( fileType, getFileName() );

    while ( readLine() )
    {
        if ( checkForWord( "//" ) ) continue;
        checkLine();
    }
    m_inFile.close();
}


const std::string&
Loader_Base :: getCurrentLineString () const
{
    return m_line;
}


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

const Vector2i
Loader_Base :: readVector2i ()
{
    int x;
    int y;
    m_inFile >> x >> y;
    return { x, y };
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
    throw std::runtime_error ( "Found unknown word: " +
                                m_line +
                               ", terminating program.");
}


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

void
Loader_Base :: prepareForLoad ()
{
    m_inFile.clear();
    m_line.clear();
}
