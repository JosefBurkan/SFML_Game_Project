#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Tile/Tile.hpp"
#include <queue>       
#include <set>         
#include <tuple>    

namespace GridPathAlgorithms
{
    // Breadth-first search algoritme
    class GridPathAlgorithm
    {

        private:
            
        public:
            void CreateRoute(sf::Vector2f start, int range, std::vector<std::vector<Tiles::Tile>>& tiles);
            void CleanGrid(std::vector<std::vector<Tiles::Tile>>& tiles);   // Fjern de markerte rutene
    };
}