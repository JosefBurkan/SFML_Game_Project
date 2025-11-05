#include "Attack.hpp"

namespace Attacks
{
    Attack::Attack(float positionX, float positionY)
    {
        hitbox.setSize({40, 40});
        hitbox.setFillColor({0, 0, 0, 0});
        hitbox.setPosition({positionX + 5, positionY + 5});
        hitbox.setFillColor({0, 0, 0, 255});
    }

    void Attack::MoveHitbox(float positionX, float positionY)
    {
        hitbox.setPosition({positionX + 5, positionY + 5});
    }

    void Attack::Draw(sf::RenderWindow& window)
    {
        window.draw(hitbox);
    }
}