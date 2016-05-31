#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <fstream>

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

        bool
        checkForWord            ( const std::string& wordToCheckFor ) const;

        bool
        endOfSection            () const;

    private:
        void
        prepareForLoad          (); //lol that name

        void
        openFile                ( const std::string& type, const std::string& path );



};

#endif // LOADER_H
