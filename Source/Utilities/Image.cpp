#include "Image.h"

#include <stdexcept>
#include <iostream>

Image :: Image ( const std::string& fileName )
{
    loadFromFile( fileName );
}

Image :: Image ( std::ifstream& inFile )
{
    loadFromStream( inFile );
}

void Image :: loadFromFile ( const std::string& fileName )
{
    std::ifstream inFile;
    inFile.open( path + fileName + extention );
    if ( !inFile.is_open() )
        throw std::runtime_error ( "Unable to load image: " + fileName + "!" );

    std::string line;
    while ( std::getline ( inFile, line ) )
    {
        m_image.append( line );
        m_image.append( "\n" );
    }
}

void Image :: loadFromStream ( std::ifstream& inFile )
{
    const static std::string terminate = "END";

    std::string line;
    while ( std::getline ( inFile, line ) )
    {
        if ( line == terminate ) break;
        m_image.append( line );
        m_image.append( "\n" );
    }

}

void Image :: draw() const
{
    std::cout << m_image << std::endl;
}
