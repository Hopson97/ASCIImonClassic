#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <fstream>


class Image
{
    public:
        Image   () = default;

        Image   ( const std::string& fileName );
        Image   ( std::ifstream& inFile );

        void loadFromFile   ( const std::string& fileName );
        void loadFromStream ( std::ifstream& inFile );

        void draw           () const;

    private:
        std::string path = "Data/Images/";
        std::string extention = ".ascimg";

        std::string m_image;
};

#endif // IMAGE_H
