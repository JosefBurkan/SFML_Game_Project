#pragma once
#include "../../config.hpp"

namespace Tiles 
{
    class Tile
    {
        public:
        sf::RectangleShape rectangle;
        int yes;

            Tile() : Tile(0.f, 0.f) {}
            
            Tile(float x, float y);

            // Lys opp ruten om en enhet har blitt valgt
            void ChangeColor(bool onSelect);

            void Select();

            void UnSelect();

            const std::pair<float, float> RetrieveTilePos() const;

            // Sjekk hva som er inni ruten
            void CheckContents();

            void Draw(sf::RenderWindow& window);

    };

}
