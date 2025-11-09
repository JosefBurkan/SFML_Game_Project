#pragma once
#include "../../../config.hpp"

namespace HealthBars
{
    class HealthBar
    {
        private:
        // De ulike lagene til healthbaren
        sf::RectangleShape rectangleGreen;
        sf::RectangleShape rectangleRed;

        public:
        HealthBar(float unitPosX, float unitPosY);
        void Draw(sf::RenderWindow& window, float health, float maxHealth);
    };
}