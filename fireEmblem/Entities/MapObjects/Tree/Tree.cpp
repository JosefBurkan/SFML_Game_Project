#include "Tree.hpp"

namespace Trees
{
    Tree::Tree(sf::Texture& texture)
        : MapObject(texture)
    {
        name = "Tree ";
        texture.setSmooth(false);
        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
        
    }


    void Tree::SetTileToOccupied()
    {
        auto& tiles = GridHandler->RetrieveAllTiles();
        std::pair<int, int> index = TransformPositionToIndex(sprite->getPosition().y, sprite->getPosition().x);
        tiles[index.first + 4][index.second + 1].IsOccupied = true;
    }
}
