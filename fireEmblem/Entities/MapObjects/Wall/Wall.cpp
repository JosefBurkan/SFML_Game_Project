#include "Wall.hpp"

namespace Walls
{
    Wall::Wall(const sf::Texture& texture)
    {
        name = "Wall ";
        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
    }
}
