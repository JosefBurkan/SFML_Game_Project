#include "Bat.hpp"
#include "MapObject.hpp"

namespace Bats
{
    Bat::Bat()
    {
        name = "Pacman ";
        texture.loadFromFile("Pacman.png");
        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
    }
}
