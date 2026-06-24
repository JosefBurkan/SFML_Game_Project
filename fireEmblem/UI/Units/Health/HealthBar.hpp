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
        HealthBar();
        void SetPosition(sf::Vector2f position);
        void Draw(sf::RenderWindow& window, int health, int maxHealth);
    };
}