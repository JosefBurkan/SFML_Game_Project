#include "Attack.hpp"

namespace Attacks
{
    Attack::Attack()
    {
        hitbox.setSize({50, 50});
        hitbox.setFillColor({0, 0, 0, 0});
    }

    void Attack::CreateHitbox(float positionX, float positionY)
    {
        hitbox.setPosition({positionX, positionY});
        hitbox.setFillColor({0, 0, 0, 255});
    }

    void Attack::MoveHitbox(float positionX, float positionY)
    {
        hitbox.setPosition({positionX, positionY});
    }

    void Attack::Draw(sf::RenderWindow& window)
    {
        window.draw(hitbox);
    }
}