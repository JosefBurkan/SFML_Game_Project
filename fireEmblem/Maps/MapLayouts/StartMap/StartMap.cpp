#include "StartMap.hpp"

namespace StartMaps
{

    void StartMap::GenerateGrid() 
    {
        gridGenerator.CreateGrid(numberOfRows, numberOfColumns);
    }

    void StartMap::LoadWindow() 
    {
        window.create(sf::VideoMode({numberOfColumns * 50, numberOfRows * 50}), "Game Window");
    }
}