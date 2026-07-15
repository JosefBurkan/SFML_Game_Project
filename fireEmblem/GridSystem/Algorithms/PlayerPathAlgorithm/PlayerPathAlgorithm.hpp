#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Tile/Tile.hpp"
#include <queue>       
#include <set>         
#include <tuple>    

namespace PlayerPathAlgorithms
{
    // Breadth-first search algoritme
    class PlayerPathAlgorithm
    {
        private:
            float coordinateY = 0;
            float coordinateX = 0;
            int travelCost = 0;

        public:
            float isActive = true;
            bool playerDetected = false;

            std::vector<Tiles::Tile> CheckAvailableTiles(sf::Vector2f start, std::vector<std::vector<Tiles::Tile>>& tiles);
            std::vector<Tiles::Tile> TracePath(Tiles::Tile* goal);
    };
}