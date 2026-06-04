#pragma once
#include "../../config.hpp"

// Deklarer klassen unit for pointer
namespace Units
{
    class Unit;
}

namespace Tiles 
{

    class Tile
    {
        public:
            sf::RectangleShape rectangle;
            bool IsOccupied = false;
            bool IsOccupiedByPlayer = false;
            int tileNumber = 0;
            bool inRange = false;                            // Har karakteren nok movement for å gå dit
            bool display = false;


            // Disse ID'ene er kun for algorithme pathfinding
            Tile* parent = nullptr;
            Units::Unit* unit = nullptr;

            int nodeID = 0;
            int parentID = 0;


            Tile() : Tile(0.f, 0.f) {}
            Tile(float x, float y);
            void ChangeColor(bool onSelect);        // Lys opp ruten om en enhet har blitt valgt
            void Select();
            void UnSelect();
            sf::Vector2f GetPosition();
            std::string OccupiedBy();
            void Draw(sf::RenderWindow& window);
            void MarkPath(); // Marker rute som spilleren kan gå til
            void MarkAttackRange();
            void UnMark();
            void Highlight(std::pair<float, float> playerPosition, int gridSizeY, int gridSizeX);




    };

}
