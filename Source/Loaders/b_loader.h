#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <fstream>

#include "Maths/vector2.h"

class Loader_Base
{
    std::string     m_line;
    std::ifstream   m_inFile;

    protected:
        virtual void
        checkLine               () = 0;

        virtual const std::string
        getFileName             () const = 0;

        void
        readFile                ( const std::string& fileType );

        const std::string&
        getCurrentLineString    () const;

        bool
        readLine                ();

        void
        readNumber              ( int& number );

        const Vector2i
        readVector2i            ();

        bool
        checkForWord            ( const std::string& wordToCheckFor ) const;

        bool
        endOfSection            ();

        void
        throwUnrecognisedWord   () const;

    private:
        void
        prepareForLoad          (); //lol that name

        void
        openFile                ( const std::string& type, const std::string& path );



};

#endif // LOADER_H
