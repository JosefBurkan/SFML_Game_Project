#include "RangedAttack.hpp"

namespace RangedAttacks
{
    RangedAttack::RangedAttack(std::string src, int atkValue, float positionX, float positionY, std::pair<float, float> directions)
        : Attack(src, atkValue, positionX, positionY)
    {
        hitbox.setSize({40, 40});
        hitbox.setFillColor({0, 0, 0, 0});
        hitbox.setPosition({positionX + 5, positionY + 5});
        hitbox.setFillColor({0, 0, 0, 255});

        assignedDirections = directions;

        std::string type = "Ranged"; 

        texture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Fireball.png");

        sprite.emplace(texture);

        sprite->setScale({5.f, 5.f});
        sprite->setPosition({positionX, positionY - 5});

        source = src;
        value = atkValue;
        
    }

    void RangedAttack::Draw(sf::RenderWindow& window)
    {
        sprite->move({assignedDirections.first, assignedDirections.second});
        hitbox.move({assignedDirections.first, assignedDirections.second});
        window.draw(*sprite);
    }
}