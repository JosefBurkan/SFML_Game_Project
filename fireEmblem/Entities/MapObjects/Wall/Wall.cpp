#include "Wall.hpp"

namespace Walls
{
    Wall::Wall(sf::Texture& texture)
        : MapObject(texture)
    {
        name = "Wall ";
        texture.setSmooth(false);

        sprite.emplace(texture);
        sprite->setScale({3.1f, 3.1f});
        
    }
}
