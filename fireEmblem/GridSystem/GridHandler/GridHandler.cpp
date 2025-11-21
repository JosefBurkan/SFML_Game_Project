#include "GridHandler.hpp"

namespace GridHandlers
{
    GridHandler::GridHandler(GridGenerators::GridGenerator& gridGenerator)
        : grid(gridGenerator)
    {
        auto& tiles = grid.RetrieveAllTiles();
        rows = tiles.size();
        columns = tiles[0].size();
    }

    void GridHandler::Movement() 
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
        // Visker vekk den valgte ruten, slik at det kun er en om gangen
        if (prevX != selectedTileX || prevY != selectedTileY) {
            tiles[prevY][prevX].ChangeColor(false);
            tiles[selectedTileY][selectedTileX].ChangeColor(true);
        }
    }

    void GridHandler::MovementWhileSelected()
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

        if (prevX != selectedTileX || prevY != selectedTileY) {
            tiles[prevY][prevX].ChangeColor(false);
            tiles[selectedTileY][selectedTileX].ChangeColor(true);
        }
    }

    void GridHandler::Attack()
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

    // Hent rute som spiller har valgt
    std::pair<int, int> GridHandler::RetrieveTile() const {
        return {selectedTileY, selectedTileX};
    }

    // Hent rute sin kordinater som spiller har valgt
    std::pair<float, float> GridHandler::SelectedTilePos() 
    {
        auto& tiles = grid.RetrieveAllTiles();

        return {tiles[selectedTileY][selectedTileX].RetrieveTilePos().first, 
                tiles[selectedTileY][selectedTileX].RetrieveTilePos().second};
    }
    // Hent alle ruter
    std::vector<std::vector<Tiles::Tile>>& GridHandler::RetrieveAllTiles()
    {
        auto& tiles = grid.RetrieveAllTiles();
        return tiles;
    }

    std::pair<int, int> GridHandler::RetrieveTileIndex()
    {
        std::pair<float, float> tilePositions = SelectedTilePos();

         // Hver rute er 50x50 størrelse, så delt på 50, vil gi tilsvarende index for ruten
        return {tilePositions.first / 50, 
                tilePositions.second / 50};
    }

    void GridHandler::SelectTile()
    {
        auto& tiles = grid.RetrieveAllTiles();
        coloredTileX = selectedTileX;
        coloredTileY = selectedTileY;

        tiles[coloredTileY][coloredTileX].Select();
    }

    void GridHandler::UnSelectTile()
    {
        auto& tiles = grid.RetrieveAllTiles();
        coloredTileX = selectedTileX;
        coloredTileY = selectedTileY;

        tiles[coloredTileY][coloredTileX].UnSelect();
    }

    // Sjekk om en tile har blitt okkupert, og hva den er okkupert av
    bool GridHandler::IsOccupied(Tiles::Tile tile)
    {
        if (tile.IsOccupied == true)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    void GridHandler::Draw(sf::RenderWindow& window) 
    {
        grid.Draw(window);
    }
}