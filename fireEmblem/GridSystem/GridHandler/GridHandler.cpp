#include "GridHandler.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"

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
        static bool firstMove = true;      // Skal gjøre det enklere å bevege presist
        static int movementDelay = 0;      // Skal gjøre det enklere å bevege presist

        rangeX = 0;
        rangeY = 0;

    // Sekvensen under er for å skape 'hakkende' bevegelse når man først beveger seg. Gjør det enklere å beve en rute om gangen
    if (movementCooldown > 2) 
    {
        if (NoMovement())      // Dersom spilleren ikke beveger seg
        {
            firstMove = true;
        }
        else if (firstMove || movementDelay == 0)    // Første bevegelse
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && selectedTileX < columns - 1) {
                selectedTileX++;
                firstMove = false;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && selectedTileX > 0) {
                selectedTileX--;
                firstMove = false;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && selectedTileY < rows - 1) {
                selectedTileY++;
                firstMove = false;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && selectedTileY > 0) {
                selectedTileY--;
                firstMove = false;
            }
            movementCooldown = 0;
        } 
        else                        // Skaper delay mellom første og de neste bevegelsene
        {
            movementDelay--;
        }

        if (firstMove)
        {
            movementDelay = 10;
        }
    }
    else 
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

            tiles[prevY][prevX].isSelected = false;
            tiles[selectedTileY][selectedTileX].isSelected = true;
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

    bool GridHandler::NoMovement()
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&  
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                return true;
            }

        return false;
    }

    void GridHandler::RestorePosition(sf::Vector2f position)
    {

    }


    // Hent rute som spiller har valgt
    Tiles::Tile GridHandler::GetSelectedTile()
    {
        auto& tiles = grid.RetrieveAllTiles();

        Tiles::Tile tile = tiles[selectedTileY][selectedTileX];

        return tile;
    }

    // Hent alle ruter
    std::vector<std::vector<Tiles::Tile>>& GridHandler::RetrieveAllTiles()
    {
        auto& tiles = grid.RetrieveAllTiles();
        
        return tiles;
    }

    // Hent uniten som ruta peker til, om den ikke er null
    Units::Unit* GridHandler::GetSelectedUnit()
    {
        auto& tiles = grid.RetrieveAllTiles();

        return tiles[selectedTileY][selectedTileX].GetUnit();
    }

    void GridHandler::ColorTile()
    {
        auto& tiles = grid.RetrieveAllTiles();

        tiles[selectedTileY][selectedTileX].Select();
    }

    void GridHandler::DeColorTile()
    {
        auto& tiles = grid.RetrieveAllTiles();

        tiles[selectedTileY][selectedTileX].UnSelect();
    }

    // Sjekk om en tile har blitt okkupert, og hva den er okkupert av
    bool GridHandler::IsOccupied(Tiles::Tile tile)
    {
        if (tile.IsOccupied || tile.unit != nullptr)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    void GridHandler::SelectTile(float coordinateY, float coordinateX)
    {
        auto& tiles = grid.RetrieveAllTiles();

        tiles[selectedTileY][selectedTileX].ChangeColor(false);

        selectedTileX = coordinateX;
        selectedTileY = coordinateY;

        tiles[coordinateY][coordinateX].ChangeColor(true);
    }

    void GridHandler::Draw(sf::RenderWindow& window) 
    {
        grid.Draw(window);
    }
}