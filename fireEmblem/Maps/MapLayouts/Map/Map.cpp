#include "Map.hpp"

namespace Maps 
{
    
    Map::Map()
    {
        wallTexture.loadFromFile("Bricks.png");

        // Lag antall vegger lik størrelsen til i
        for (int i = 0; i < 5; i++)
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


    void Map::SetGridMovement(GridMovements::GridMovement& movement)
    {
        gridMovementPtr = &movement;

        // Assign to every object manually (or put them in a vector to simplify)
        mapObject2.SetGrid(*gridMovementPtr);
        walls[0].SetGrid(*gridMovementPtr);
        walls[1].SetGrid(*gridMovementPtr);
        walls[2].SetGrid(*gridMovementPtr);
        walls[3].SetGrid(*gridMovementPtr);
        walls[4].SetGrid(*gridMovementPtr);
        mapObject2.SetGrid(*gridMovementPtr);
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

        walls[0].Position(gridTiles[1][1].RetrieveTilePos().first, gridTiles[1][1].RetrieveTilePos().second);
        walls[1].Position(gridTiles[1][2].RetrieveTilePos().first, gridTiles[1][2].RetrieveTilePos().second);
        walls[2].Position(gridTiles[1][3].RetrieveTilePos().first, gridTiles[1][3].RetrieveTilePos().second);
        walls[3].Position(gridTiles[1][4].RetrieveTilePos().first, gridTiles[1][4].RetrieveTilePos().second);
        walls[4].Position(gridTiles[2][4].RetrieveTilePos().first, gridTiles[2][4].RetrieveTilePos().second);

        walls[0].SetTileToOccupied();
        walls[1].SetTileToOccupied();
        walls[2].SetTileToOccupied();
        walls[3].SetTileToOccupied();
        walls[4].SetTileToOccupied();

        mapObject2.Position(gridTiles[2][2].RetrieveTilePos().first, gridTiles[2][2].RetrieveTilePos().second);

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
        mapObject2.Draw(window);
    }
}