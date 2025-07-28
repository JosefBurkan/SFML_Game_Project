#include "Bat.hpp"

namespace Bats
{
    Bat::Bat()
    {
        name = "Bat ";
        texture.loadFromFile("Pacman.png");
        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
    }
}
