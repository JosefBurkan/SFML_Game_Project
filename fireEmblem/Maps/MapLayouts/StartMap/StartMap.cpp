#include "StartMap.hpp"

namespace StartMaps
{


    void StartMap::LoadWindow() 
    {
        window.create(sf::VideoMode({1280, 720}), "Best G4ME");
    }
}