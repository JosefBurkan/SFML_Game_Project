#pragma once
#include "../../config.hpp"

namespace Attacks
{
    class Attack 
    {
        protected:
        std::string type = "Attack";
        std::string source = "None";
        int value = 1;


        public:
            sf::RectangleShape hitbox;
            Attack(std::string src, int atkValue, sf::Vector2f position);
            void MoveHitbox(sf::Vector2f position);
            std::string GetSource();
            int GetValue();
            virtual void Draw(sf::RenderWindow& window);
    };
}