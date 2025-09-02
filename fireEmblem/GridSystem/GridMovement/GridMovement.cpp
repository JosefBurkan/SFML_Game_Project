#include "GridMovement.hpp"

namespace GridMovements
{
    GridMovement::GridMovement(GridGenerators::GridGenerator& gridGenerator)
        : grid(gridGenerator)
    {
        auto& tiles = grid.RetrieveAllTiles();
        rows = tiles.size();
        columns = tiles[0].size();
    }

      void GridMovement::Movement() 
    {
        auto& tiles = grid.RetrieveAllTiles();
        int prevX = selectedTileX;
        int prevY = selectedTileY;

        rangeX = 0;
        rangeY = 0;

        if (movementCooldown > 2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && selectedTileX < columns - 1) {
                selectedTileX++;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && selectedTileX > 0) {
                selectedTileX--;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && selectedTileY < rows - 1) {
                selectedTileY++;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && selectedTileY > 0) {
                selectedTileY--;
            }
            movementCooldown = 0;
        } else 
        {
            movementCooldown++;
        }
        if (prevX != selectedTileX || prevY != selectedTileY) {
            tiles[prevY][prevX].ChangeColor(false);
            tiles[selectedTileY][selectedTileX].ChangeColor(true);
        }
    }

    void GridMovement::MovementWhileSelected()
    {
        auto& tiles = grid.RetrieveAllTiles();
        int prevX = selectedTileX;
        int prevY = selectedTileY;

        rangeX = 0;
        rangeY = 0;


        if (movementCooldown > 2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && selectedTileX < columns - 1) {
                selectedTileX++;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && selectedTileX > 0) {
                selectedTileX--;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && selectedTileY < rows - 1) {
                selectedTileY++;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && selectedTileY > 0) {
                selectedTileY--;
            }
            movementCooldown = 0;
        } else 
        {
            movementCooldown++;
            selectedTileX = prevX;
            selectedTileY = prevY;
        }

        

    }

    void GridMovement::Attack()
    {
        auto& tiles = grid.RetrieveAllTiles();

        int prevX = selectedTileX;
        int prevY = selectedTileY;

        if (movementCooldown > 2) 
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && selectedTileX < columns - 1 && rangeX <= 0 && rangeY == 0) {
                selectedTileX++;
                rangeX++;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && selectedTileX > 0 && rangeX >= 0 && rangeY == 0) {
                selectedTileX--;
                rangeX--;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && selectedTileY < rows - 1 && rangeY <= 0 && rangeX == 0) {
                selectedTileY++;
                rangeY++;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && selectedTileY > 0 && rangeY >= 0 && rangeX == 0) {
                selectedTileY--;
                rangeY--;
            }
            movementCooldown = 0;
        } else 
        {
            movementCooldown++;
        }

        if (prevX != selectedTileX || prevY != selectedTileY) 
        {
            tiles[prevY][prevX].ChangeColor(false);
            tiles[selectedTileY][selectedTileX].ChangeColor(true);
        }

    }    

    std::vector<std::vector<Tiles::Tile>>& GridMovement::RetrieveAllTiles()
    {
        auto& tiles = grid.RetrieveAllTiles();
        return tiles;
    }

}
