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
            RangedAttack(float positionX, float positionY, std::pair<float, float> directions);
            void Draw(sf::RenderWindow& window) override;
    };
}