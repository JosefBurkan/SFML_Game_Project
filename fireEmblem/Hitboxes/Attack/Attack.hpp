#pragma once
#include "../../config.hpp"

namespace Attacks
{
    class Attack 
    {
        protected:
        std::string type = "Attack";


        public:
            sf::RectangleShape hitbox;
            Attack(float positionX, float positionY);
            void MoveHitbox(float positionX, float positionY);
            virtual void Draw(sf::RenderWindow& window);
    };
}