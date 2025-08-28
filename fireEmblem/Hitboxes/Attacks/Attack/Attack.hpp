#pragma once
#include "../../../config.hpp"

namespace Attacks
{
    class Attack 
    {
        private:

        public:
            sf::RectangleShape hitbox;
            Attack(float positionX, float positionY);
            void MoveHitbox(float positionX, float positionY);
            void Draw(sf::RenderWindow& window);
    };
}