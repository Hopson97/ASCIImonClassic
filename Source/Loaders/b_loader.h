#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <fstream>
#include <map>
#include <functional>

#include "Image.h"

#include "../Game/Maths/vector2.h"


class Loader_Base
{
    std::map < std::string, std::function<void(void)> > m_keywords;
    std::map < std::string, int* > m_keywordNums;
    std::map < std::string, unsigned* > m_keywordUnsigned;
    std::map < std::string, std::string* > m_keywordStrings;

    std::string     m_line;
    std::ifstream   m_inFile;

    protected:
        virtual void checkLineForKeyword        ();

        virtual const std::string getFileName   () const = 0;

        void addKeyword                         ( std::function<void(void)>,    const std::string& keyword);
        void addKeyword                         ( int& num,                     const std::string& keyword);
        void addKeyword                         ( unsigned& num,                const std::string& keyword);
        void addKeyword                         ( std::string* data,            const std::string& keyword);

        void readFile                           ( const std::string& fileType );

        const std::string& getCurrentLineString () const;

        bool readLine           ();
        void readVector2i       ( Vector2i& vector );
        void readImage          ( Image& image );

        void readNumber         ( int& number );
        void readNumber         ( unsigned& number );

        void readString         ( std::string& data );

        bool checkForWord       ( const std::string& wordToCheckFor ) const;

        bool endOfSection       ();

        void throwUnrecognisedWord   () const;

    private:
        void prepareForLoad (); //lol that name

        void  openFile      ( const std::string& type, const std::string& path );

        template <typename T, typename R>
        void checkMap ( const std::map< std::string, T>& map, std::function<void(R)> func )
        {
            for ( auto& keyword : map )
            {
                if ( checkForWord( keyword.first ) )
                {
                    func( *keyword.second );
                    return;
                }
            }
        }



};

#endif // LOADER_H
