#include "MapObject.hpp"

namespace MapObjects
{

    MapObject::MapObject()
    {
        texture.loadFromFile("Bricks.png");
        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
    }

    void MapObject::SetGrid(GridHandlers::GridHandler& grid)
    {
        this->GridHandler = &grid;
    }

    GridHandlers::GridHandler& MapObject::FetchGrid() 
    {
        return *GridHandler;
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
        if (!GridHandler)
        {
            std::cout << "GridHandler is nullptr!" << std::endl;
            return;
        }

        auto& tiles = GridHandler->RetrieveAllTiles();
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