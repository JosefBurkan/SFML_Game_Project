#pragma once
#include "../../../config.hpp"
#include "../BackgroundTiles/BackgroundTile.hpp"
#include "../../../GridSystem/GridMovement/GridMovement.hpp"

namespace Backgrounds1
{
    class Background1
    {
        public:
        BackgroundTiles::BackgroundTile backgroundTile;
        GridMovements::GridMovement& movement;

        Background1(GridMovements::GridMovement& gridMovement);
        void LoadTileMapFromFile();
        void Draw(sf::RenderWindow& window);

    };

}
