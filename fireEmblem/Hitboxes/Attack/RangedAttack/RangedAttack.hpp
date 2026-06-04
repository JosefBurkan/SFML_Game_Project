#pragma once
#include "../../../config.hpp"
#include "../Attack.hpp"

namespace RangedAttacks
{
    class RangedAttack : public Attacks::Attack
    {
        private:
            std::pair<float, float> assignedDirections;
            sf::Texture texture; 
            std::optional<sf::Sprite> sprite;

        public:
            RangedAttack(std::string src, int atkValue, sf::Vector2f position, std::pair<float, float> directions);
            void Draw(sf::RenderWindow& window) override;
    };
}