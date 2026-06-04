#include "Map.hpp"

namespace Maps 
{
    
    Map::Map()
    {
        wallTexture.loadFromFile(std::string(ASSETS_DIR) + "Maps/Forest/Bricks.png");
        treeTexture.loadFromFile(std::string(ASSETS_DIR) + "Maps/Forest/Tree-1.png");

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

        walls[0].SetPosition(gridTiles[5][1].GetPosition());
        walls[1].SetPosition(gridTiles[5][2].GetPosition());
        walls[2].SetPosition(gridTiles[5][3].GetPosition());
        walls[3].SetPosition(gridTiles[1][0].GetPosition());
        walls[8].SetPosition(gridTiles[5][0].GetPosition());
        walls[4].SetPosition(gridTiles[1][1].GetPosition());
        walls[5].SetPosition(gridTiles[1][2].GetPosition());
        walls[6].SetPosition(gridTiles[1][3].GetPosition());
        walls[7].SetPosition(gridTiles[1][4].GetPosition());

        for (auto wall : walls)
        {
            wall.SetTileToOccupied();
        }

        trees[0].SetPosition(gridTiles[5][2].GetPosition());
        trees[1].SetPosition(gridTiles[3][9].GetPosition());
        
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