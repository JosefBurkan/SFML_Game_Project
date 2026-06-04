#include "Attack.hpp"

namespace Attacks
{
    Attack::Attack(std::string src, int atkValue, sf::Vector2f position)
    {
        hitbox.setSize({40, 40});
        hitbox.setFillColor({0, 0, 0, 0});
        hitbox.setPosition({position.x + 5, position.y + 5});
        hitbox.setFillColor({0, 0, 0, 255});

        source = src;
        value = atkValue;
    }

    void Attack::MoveHitbox(sf::Vector2f position)
    {
        hitbox.setPosition({position.x + 5, position.y + 5});
    }

    void Attack::Draw(sf::RenderWindow& window)
    {
        
    }

    std::string Attack::GetSource()
    {
        return source;
    }

    int Attack::GetValue()
    {
        return value;
    }
}