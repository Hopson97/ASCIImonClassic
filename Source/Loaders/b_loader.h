#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <fstream>
#include <map>
#include <functional>

#include "../Game/Maths/vector2.h"


class Loader_Base
{
    std::map < std::string, std::function<void(void)> > m_keywords;


    std::string     m_line;
    std::ifstream   m_inFile;

    protected:
        void addKeyword                         ( std::function<void(void)>, const std::string& keyword);

        virtual void checkLineForKeyword        ();

        virtual const std::string getFileName   () const = 0;

        void readFile                           ( const std::string& fileType );

        const std::string& getCurrentLineString () const;

        bool readLine           ();
        void readNumber         ( int& number );
        void readVector2i       ( Vector2i& vector );

        bool checkForWord       ( const std::string& wordToCheckFor ) const;

        bool endOfSection       ();

        void throwUnrecognisedWord   () const;

    private:
        void prepareForLoad (); //lol that name

        void  openFile      ( const std::string& type, const std::string& path );



};

#endif // LOADER_H
