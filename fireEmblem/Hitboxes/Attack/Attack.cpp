#include "Attack.hpp"

namespace Attacks
{
    Attack::Attack(std::string src, int atkValue, float positionX, float positionY)
    {
        hitbox.setSize({40, 40});
        hitbox.setFillColor({0, 0, 0, 0});
        hitbox.setPosition({positionX + 5, positionY + 5});
        hitbox.setFillColor({0, 0, 0, 255});

        source = src;
        value = atkValue;
    }

    void Attack::MoveHitbox(float positionX, float positionY)
    {
        hitbox.setPosition({positionX + 5, positionY + 5});
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