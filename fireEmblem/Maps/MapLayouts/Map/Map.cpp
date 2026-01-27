#include "Map.hpp"

namespace Maps 
{
    
    Map::Map()
    {
        wallTexture.loadFromFile(std::string(ASSETS_DIR) + "Bricks.png");
        treeTexture.loadFromFile(std::string(ASSETS_DIR) + "Tree-1.png");

        wallTexture.setSmooth(false);
        treeTexture.setSmooth(false);

        // Lag antall vegger lik størrelsen til i
        for (int i = 0; i < 9; i++)
        {
            walls.emplace_back(wallTexture);
        }

        for (int i = 0; i < 2; i++)
        {
            trees.emplace_back(treeTexture);
        }

    }

    GridGenerators::GridGenerator& Map::GenerateGrid() 
    {
        gridGenerator.CreateGrid(numberOfRows, numberOfColumns);

        return gridGenerator;
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

        walls[0].SetGrid(*GridHandlerPtr);
        walls[1].SetGrid(*GridHandlerPtr);
        walls[2].SetGrid(*GridHandlerPtr);
        walls[3].SetGrid(*GridHandlerPtr);
        walls[4].SetGrid(*GridHandlerPtr);
        walls[5].SetGrid(*GridHandlerPtr);
        walls[6].SetGrid(*GridHandlerPtr);
        walls[7].SetGrid(*GridHandlerPtr);
        walls[8].SetGrid(*GridHandlerPtr);

        trees[0].SetGrid(*GridHandlerPtr);
        trees[1].SetGrid(*GridHandlerPtr);
    }

    void Map::LoadWindow() 
    {
        window.create(sf::VideoMode({720, 480}), "AAAA ew");
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

        walls[0].Position(gridTiles[1][5].RetrieveTilePos());
        walls[1].Position(gridTiles[2][5].RetrieveTilePos());
        walls[2].Position(gridTiles[3][5].RetrieveTilePos());
        walls[3].Position(gridTiles[0][1].RetrieveTilePos());
        walls[8].Position(gridTiles[0][5].RetrieveTilePos());
        walls[4].Position(gridTiles[1][1].RetrieveTilePos());
        walls[5].Position(gridTiles[2][1].RetrieveTilePos());
        walls[6].Position(gridTiles[3][1].RetrieveTilePos());
        walls[7].Position(gridTiles[4][1].RetrieveTilePos());

        for (auto wall : walls)
        {
            wall.SetTileToOccupied();
        }

        trees[0].Position(gridTiles[2][5].RetrieveTilePos());
        trees[1].Position(gridTiles[9][3].RetrieveTilePos());
        
        for (auto iTree : trees)
        {
            iTree.SetTileToOccupied();
        }
    }

    // Tegn baneobjekter, feks. trær
    void Map::DrawMapObjects(sf::RenderWindow& window)
    {
        for (auto wall : walls)
        {
            wall.Draw(window);
        }

        for (auto iTree : trees)
        {
            iTree.Draw(window);
        }
    }
}