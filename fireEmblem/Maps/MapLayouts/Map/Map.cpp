#include "Map.hpp"

namespace Maps 
{
    
    Map::Map()
    {
        wallTexture.loadFromFile(std::string(ASSETS_DIR) + "Bricks.png");

        // Lag antall vegger lik størrelsen til i
        for (int i = 0; i < 8; i++)
        {
            walls.emplace_back(wallTexture);
        }

    }

    void Map::GenerateGrid() 
    {
        gridGenerator.CreateGrid(numberOfRows, numberOfColumns);
    }

    // returner gridGenerator med verdiene til den eksisterende gridden
    GridGenerators::GridGenerator& Map::FetchGrid()
    {
        return gridGenerator;   
    }


    void Map::SetGridMovement(GridHandlers::GridHandler& movement)
    {
        GridHandlerPtr = &movement;

        // Tildel objektene rutenettet de hører til
        mapObject2.SetGrid(*GridHandlerPtr);
        walls[0].SetGrid(*GridHandlerPtr);
        walls[1].SetGrid(*GridHandlerPtr);
        walls[2].SetGrid(*GridHandlerPtr);
        walls[3].SetGrid(*GridHandlerPtr);
        walls[4].SetGrid(*GridHandlerPtr);
        walls[5].SetGrid(*GridHandlerPtr);
        walls[6].SetGrid(*GridHandlerPtr);
        walls[7].SetGrid(*GridHandlerPtr);
    }

    void Map::LoadWindow() 
    {
        window.create(sf::VideoMode({numberOfColumns * 50, numberOfRows * 50}), "Game Window");
    }

    // Last inn kameraet
    sf::View Map::LoadView()
    {
        sf::Vector2f vec1(0.f, 0.0f);
        sf::Vector2f vec2(numberOfColumns * 25, numberOfRows * 25);
        sf::View view(sf::FloatRect(vec1, vec2));
        return view;
    }

    // Sett objektet sin posisjon
    void Map::SpawnObjects()
    {
        auto& gridTiles = gridGenerator.RetrieveAllTiles();

        walls[0].Position(gridTiles[1][4].RetrieveTilePos().first, gridTiles[1][4].RetrieveTilePos().second);
        walls[1].Position(gridTiles[2][4].RetrieveTilePos().first, gridTiles[2][4].RetrieveTilePos().second);
        walls[2].Position(gridTiles[3][4].RetrieveTilePos().first, gridTiles[3][4].RetrieveTilePos().second);
        walls[3].Position(gridTiles[4][4].RetrieveTilePos().first, gridTiles[4][4].RetrieveTilePos().second);
        walls[4].Position(gridTiles[1][1].RetrieveTilePos().first, gridTiles[1][1].RetrieveTilePos().second);
        walls[5].Position(gridTiles[2][1].RetrieveTilePos().first, gridTiles[2][1].RetrieveTilePos().second);
        walls[6].Position(gridTiles[3][1].RetrieveTilePos().first, gridTiles[3][1].RetrieveTilePos().second);
        walls[7].Position(gridTiles[4][1].RetrieveTilePos().first, gridTiles[4][1].RetrieveTilePos().second);

        walls[0].SetTileToOccupied();
        walls[1].SetTileToOccupied();
        walls[2].SetTileToOccupied();
        walls[3].SetTileToOccupied();
        walls[4].SetTileToOccupied();
        walls[5].SetTileToOccupied();
        walls[6].SetTileToOccupied();
        walls[7].SetTileToOccupied();

        mapObject2.Position(gridTiles[8][8].RetrieveTilePos().first, gridTiles[8][8].RetrieveTilePos().second);

        mapObjects.push_back(mapObject2);


    }

    // Tegn baneobjekter, feks. trær
    void Map::DrawMapObjects(sf::RenderWindow& window)
    {
        walls[0].Draw(window);
        walls[1].Draw(window);
        walls[2].Draw(window);
        walls[3].Draw(window);
        walls[4].Draw(window);
        walls[5].Draw(window);
        walls[6].Draw(window);
        walls[7].Draw(window);
        mapObject2.Draw(window);
    }
}