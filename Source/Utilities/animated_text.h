#ifndef ANIMATED_TEXT_H
#define ANIMATED_TEXT_H

#include <string>

#include "Image.h"

class Animated_Text
{
    public:
        Animated_Text   ( const Image& image, double time = defaultTime );
        Animated_Text   ( const std::string& text, double time = defaultTime );
        Animated_Text   ( const std::string& text, const Image& image, double time = defaultTime );

        void display    ();

        void setText    ( const std::string& text );
        void operator = ( const std::string& text );

        static void quickText   ( const std::string& text, double time = defaultTime );
        static void quickText   ( const std::string& text, const Image& image, double time = defaultTime );
    private:
        std::string m_text;

        double m_time; //time between each char printing

        const Image* m_image = nullptr;

        constexpr static double defaultTime = 0.08;
};

#endif // ANIMATED_TEXT_H
