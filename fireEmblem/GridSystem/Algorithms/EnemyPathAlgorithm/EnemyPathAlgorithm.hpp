#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Tile/Tile.hpp"
#include <queue>       
#include <set>         
#include <tuple>    

namespace EnemyPathAlgorithms
{
    // Breadth-first search algoritme
    class EnemyPathAlgorithm
    {
        private:
            float coordinateY = 0;
            float coordinateX = 0;
            int travelCost = 0;
        public:
            float isActive = true;
            bool playerDetected = false;
            std::pair<float, float> CheckAvailableTiles(int startY, int startX, int range, std::vector<std::vector<Tiles::Tile>>& tiles);
    };
}