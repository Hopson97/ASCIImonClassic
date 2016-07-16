#include "b_loader.h"

#include <stdexcept>
#include <iostream>

void Loader_Base :: addKeyword ( std::function<void(void)> function, const std::string& keyword)
{
    m_keywords[keyword] = function;
}

void Loader_Base :: addKeyword(int& num, const std::string& keyword)
{
    m_keywordNums[keyword] = &num;
}

void Loader_Base :: addKeyword(unsigned& num, const std::string& keyword)
{
    m_keywordUnsigned[keyword] = &num;
}

void Loader_Base :: addKeyword ( std::string* data, const std::string& keyword)
{
    m_keywordStrings[keyword] = data;
}

void Loader_Base :: addKeyword ( unsigned& n1, unsigned& n2,       const std::string& keyword)
{
    Multi_Key_Section data;
    data.a = &n1;
    data.b = &n2;

    m_multiKeywords[keyword] = data;
}



//Fully reads the file, using the functions and keyword pairs passed in from a derived class
void Loader_Base :: readFile ( const std::string& fileType )
{
    prepareForLoad();
    openFile( fileType, getFileName() );

    while ( readLine() )
    {
        if ( checkForWord( "//" ) ) continue;
        if ( checkForWord( "HARDEND") ) break;
        checkLineForKeyword();
    }
    m_inFile.close();

}

//Goes through the function/ keyword list and calls a function if the keyword matches the read line
//If it does not, it means an unrecognised word is found, of which needs to be dealt with
void Loader_Base :: checkLineForKeyword ()
{
    for ( auto& keyword : m_keywords )
    {
        if ( checkForWord( keyword.first ) )
        {
            keyword.second();   //keyword.second is an std::function
            return;
        }
    }

//    checkMap( m_keywordNums, std::bind( &Loader_Base::readNumber, this) );

    for ( auto& keyword : m_keywordNums )
    {
        if ( checkForWord( keyword.first ) )
        {
            readNumber( *keyword.second );
            return;
        }
    }
    for ( auto& keyword : m_keywordUnsigned )
    {
        if ( checkForWord( keyword.first ) )
        {
            readNumber( *keyword.second );
            return;
        }
    }

//    checkMap( m_keywordStrings, std::bind( &Loader_Base::readString, this) );

    for ( auto& keyword : m_keywordStrings )
    {
        if ( checkForWord( keyword.first ) )
        {
            readString( *keyword.second );
            return;
        }
    }

    for ( auto& keyword : m_multiKeywords )
    {
        if ( checkForWord( keyword.first ) )
        {
            readNumber( *keyword.second.a );
            readNumber( *keyword.second.b );
            return;
        }
    }
    throwUnrecognisedWord();
}


const std::string& Loader_Base :: getCurrentLineString () const
{
    return m_line;
}


//Bunch of reader functions for the derived classes
bool Loader_Base :: readLine ()
{
    return std::getline( m_inFile, m_line );
}


void Loader_Base :: readVector2i ( Vector2i& vector )
{
    m_inFile >> vector.x >> vector.y;
}


void Loader_Base :: readImage( Image& image )
{
    image.loadFromStream( m_inFile );
}


void Loader_Base :: readNumber ( int& number )
{
    m_inFile >> number;
}


void Loader_Base :: readNumber ( unsigned& number )
{
    m_inFile >> number;
}


void Loader_Base :: readString ( std::string& data )
{
    readLine();
    data = m_line;
}


bool Loader_Base :: checkForWord ( const std::string& wordToCheckFor ) const
{
    //return m_line.find ( wordToCheckFor ) != std::string::npos;
    return m_line == wordToCheckFor;
}


void Loader_Base :: throwUnrecognisedWord   () const
{
    if ( m_line == "") return;
    throw std::runtime_error ( "\tFound unknown word: " +
                                m_line +
                               ", terminating program.\
                               \n");
}

//Each section of the files is marked by a END, and this checks for that
bool Loader_Base :: endOfSection ()
{
    readLine();
    return checkForWord( "END" );
}



void Loader_Base :: openFile ( const std::string& type, const std::string& path )
{
    m_inFile.open ( path );

    if ( !m_inFile.is_open() ) {
        throw std::runtime_error ( "File type of type \"" + type +
                                  "\" at \"" + path +
                                  "\" does not exist.");
    }
}


//: ^ )
void Loader_Base :: prepareForLoad ()
{
    m_inFile.clear();
    m_line.clear();
}
