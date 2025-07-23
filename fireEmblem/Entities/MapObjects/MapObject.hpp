#pragma once
#include "../../config.hpp"
#include "../../GridSystem/Tile/Tile.hpp"

namespace MapObjects
{
    class MapObject
    {
        public:
        sf::Texture texture;
        std::optional<sf::Sprite> sprite;
        std::string name = "Testobjekt ";

        
        MapObject();
        sf::Sprite GenerateSprite();
        sf::Sprite& RetrieveSprite();
        std::pair<float, float> printPos();
    };
}