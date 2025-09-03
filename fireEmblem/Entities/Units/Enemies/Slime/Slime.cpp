#include "Slime.hpp"

namespace Slimes
{
    Slime::Slime(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks)
        : Unit(gridReference, map, attacks)
    {
        if (!texture.loadFromFile(std::string(ASSETS_DIR) + "Pixel-Bat.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        name = "Slime";

        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({450.f, 450.f});
    }

}