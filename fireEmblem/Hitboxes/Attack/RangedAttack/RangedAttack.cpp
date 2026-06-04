#include "RangedAttack.hpp"

namespace RangedAttacks
{
    RangedAttack::RangedAttack(std::string src, int atkValue, sf::Vector2f position, std::pair<float, float> directions)
        : Attack(src, atkValue, position)
    {
        hitbox.setSize({40, 40});
        hitbox.setFillColor({0, 0, 0, 0});
        hitbox.setPosition({position.x + 5, position.y + 5});
        hitbox.setFillColor({0, 0, 0, 255});

        assignedDirections = directions;

        std::string type = "Ranged"; 

        texture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Fireball.png");

        sprite.emplace(texture);

        sprite->setScale({5.f, 5.f});
        sprite->setPosition({position.x, position.y - 5});

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