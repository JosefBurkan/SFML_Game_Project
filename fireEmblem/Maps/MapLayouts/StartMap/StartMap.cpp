#include "StartMap.hpp"

namespace StartMaps
{

    void StartMap::GenerateGrid() 
    {
        gridGenerator.CreateGrid(numberOfRows, numberOfColumns);
    }

    void StartMap::LoadWindow() 
    {
        window.create(sf::VideoMode({1280, 720}), "AAAA");
    }
}