#include "Enemy.hpp"

namespace Enemies
{
    Enemy::Enemy(GridGenerators::GridGenerator& gridReference, Maps::Map& map)
        : Unit(gridReference, map)
    {
        if (!texture.loadFromFile("pixel-bat.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        sprite.emplace(texture);
        sprite->setScale({0.1f, 0.1f});
        sprite->setPosition({200.f, 200.f});

    }
}