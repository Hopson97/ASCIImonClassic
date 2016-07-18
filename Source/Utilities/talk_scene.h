#ifndef TALK_SCENE_H
#define TALK_SCENE_H

#include <string>
#include <vector>
#include <map>

#include "animated_text.h"

class Talk_Scene
{
    public:
        Talk_Scene      ();
        Talk_Scene      ( const std::string& file, const Image& image );

        void begin      ();

        void setVar     ( const std::string& varName, const std::string& replaceWith );

    private:
        void readFile   ( const std::string& fileName );

        std::string constructString ( const std::string& line ) const;

        void loopThroughString  ( std::string& finalString, bool& varFound ) const;

        void checkCharForVar    ( std::string& finalString, bool& varFound, const int i ) const;


        Animated_Text m_animText;
        std::vector<std::string > m_lines;
        std::map<std::string, std::string> m_variables;
        std::string m_fileName;
};

#endif // TALK_SCENE_H
