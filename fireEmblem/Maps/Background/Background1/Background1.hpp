#pragma once
#include "../../../config.hpp"
#include "../BackgroundTiles/BackgroundTile.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/GridHandler/GridHandler.hpp"

namespace Backgrounds1
{
    class Background1
    {
        public:
        BackgroundTiles::BackgroundTile backgroundTile;
        GridHandlers::GridHandler& movement;

        Background1(GridHandlers::GridHandler& GridHandler);
        void LoadTileMapFromFile();
        void Draw(sf::RenderWindow& window);

    };

}
