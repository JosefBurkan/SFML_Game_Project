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
    
    void GridMovement::Movement() {
        auto& tiles = grid.RetrieveAllTiles();

        int prevX = selectedTileX;
        int prevY = selectedTileY;

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

    // Hent rute som spiller har valgt
    std::pair<int, int> GridMovement::RetrieveTile() const {
        return {selectedTileX, selectedTileY};
    }

    // Hent rute sin kordinater som spiller har valgt
    std::pair<float, float> GridMovement::SelectedTilePos() 
    {
        auto& tiles = grid.RetrieveAllTiles();

        return {tiles[selectedTileY][selectedTileX].RetrieveTilePos().first, 
                tiles[selectedTileY][selectedTileX].RetrieveTilePos().second};
    }

    // Hent alle ruter
    std::vector<std::vector<Tiles::Tile>>& GridMovement::RetrieveAllTiles()
    {
        auto& tiles = grid.RetrieveAllTiles();
        return tiles;
    }

    void GridMovement::RetrieveTileByPositions(float positionX, float positionY)
    {
        auto& tiles = grid.RetrieveAllTiles();

    }

    void GridMovement::SelectTile()
    {
        auto& tiles = grid.RetrieveAllTiles();
        coloredTileX = selectedTileX;
        coloredTileY = selectedTileY;

        tiles[coloredTileY][coloredTileX].Select();
    }

    void GridMovement::UnSelectTile()
    {
        auto& tiles = grid.RetrieveAllTiles();
        coloredTileX = selectedTileX;
        coloredTileY = selectedTileY;

        tiles[coloredTileY][coloredTileX].UnSelect();
    }

    // Sjekk om en tile har blitt okkupert, og hva den er okkupert av
    bool GridMovement::IsOccupied(Tiles::Tile tile)
    {

        if (tile.isOccupiedByEnemy == true)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    void GridMovement::PrintGrid()
    {
        auto& tiles = grid.RetrieveAllTiles();
        std::cout << tiles[3][3].RetrieveTilePos().first;
    }

}