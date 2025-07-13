#include "Map.cpp"
using namespace Maps;

namespace Maps
{
    class StartMap : public Map
    {
        unsigned int numberOfColumns = 15;
        unsigned int numberOfRows = 16;

        public: 
            void GenerateGrid() 
            {
                gridGenerator.CreateGrid(numberOfRows, numberOfColumns);
            }

            void LoadWindow() 
            {
                window.create(sf::VideoMode({numberOfColumns * 50, numberOfRows * 50}), "Game Window");
            }
    };
}