#include "RangedAttack.hpp"

namespace RangedAttacks
{
    RangedAttack::RangedAttack(float positionX, float positionY, std::pair<float, float> directions)
        : Attack(positionX, positionY)
    {
        hitbox.setSize({40, 40});
        hitbox.setFillColor({0, 0, 0, 0});
        hitbox.setPosition({positionX + 5, positionY + 5});
        hitbox.setFillColor({0, 0, 0, 255});

        assignedDirections = directions;

        std::string type = "Ranged"; 

        texture.loadFromFile(std::string(ASSETS_DIR) + "Units/Fireball.png");

        sprite.emplace(texture);

        sprite->setScale({5.f, 5.f});
        sprite->setPosition({positionX, positionY - 5});
        
    }

    void RangedAttack::Draw(sf::RenderWindow& window)
    {
        sprite->move({assignedDirections.first, assignedDirections.second});
        hitbox.move({assignedDirections.first, assignedDirections.second});
        window.draw(*sprite);
    }
}