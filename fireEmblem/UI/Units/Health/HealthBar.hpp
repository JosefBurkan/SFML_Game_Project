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
        int width = 50;

        public:
        HealthBar(float unitPosX, float unitPosY);
        void Draw(sf::RenderWindow& window, int health, int maxHealth);
    };
}