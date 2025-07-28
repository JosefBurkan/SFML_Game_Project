#include "MapObject.hpp"

namespace MapObjects
{

    MapObject::MapObject()
    {
        texture.loadFromFile("Bricks.png");
        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});

    }

    void MapObject::SetGrid(GridMovements::GridMovement& grid)
    {
        this->gridMovement = &grid;
    }

    GridMovements::GridMovement& MapObject::FetchGrid() 
    {
        return *gridMovement;
    }

    sf::Sprite& MapObject::RetrieveSprite() 
    {
        return *sprite;
    }

    std::pair<int, int> MapObject::TransformPositionToIndex(float positionX, float positionY)
    {
        return{positionX/50, positionY/50}; // Hver rute er 50x50 størrelse, så delt på 50, vil gi tilsvarende index for ruten

    }

    std::pair<float, float> MapObject::printPos()
    {
        return {sprite->getPosition().x, sprite->getPosition().y};
    }

    // endre statusen til ruten som objektet står på
    void MapObject::SetTileToOccupied()
    {
        // Stopper funksjonen fra å kjøre før gridmovment har fått verdi
        if (!gridMovement)
        {
            std::cout << "gridMovement is nullptr!" << std::endl;
            return;
        }

        auto& tiles = gridMovement->RetrieveAllTiles();
        std::pair<int, int> index = TransformPositionToIndex(sprite->getPosition().x, sprite->getPosition().y);
        tiles[index.first][index.second].isOccupiedByEnemy = true;
    }

    // Flytt til en annen rute
    void MapObject::Position(float positionX, float positionY)
    {
        sprite->setPosition({positionX, positionY});
    }

    void MapObject::Draw(sf::RenderWindow& window) 
    {
        window.draw(*sprite);
    }


 


}