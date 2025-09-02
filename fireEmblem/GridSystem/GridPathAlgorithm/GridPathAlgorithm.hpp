#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Tile/Tile.hpp"
#include <vector>      
#include <queue>       
#include <set>         
#include <tuple>    

namespace GridPathAlgorithms
{
    // Breadth-first search algoritme
    class GridPathAlgorithm
    {
        public:

            void CheckAvailableTiles(int startX, int startY, int range, std::vector<std::vector<Tiles::Tile>>& tiles);
            void CleanGrid(std::vector<std::vector<Tiles::Tile>>& tiles);   // Fjern de markerte rutene
    };
}