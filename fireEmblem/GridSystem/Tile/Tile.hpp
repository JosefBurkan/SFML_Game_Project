#pragma once
#include "../../config.hpp"

namespace Tiles 
{
    class Tile
    {
        public:
        sf::RectangleShape rectangle;
        bool IsOccupied = false;
        int tileNumber = 0;
        bool inRange;                            // Har karakteren nok movement for å gå dit
        bool a;

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
            // Marker rute som spilleren kan gå til
            void MarkPath();
            // Marker rute som spilleren kan angripe
            void MarkAttackRange();                          
            void Highlight(std::pair<float, float> playerPosition, int gridSizeY, int gridSizeX);

    };

}
