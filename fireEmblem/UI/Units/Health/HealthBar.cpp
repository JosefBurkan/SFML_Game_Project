#include "HealthBar.hpp"

namespace HealthBars
{
    // Opprett healthbaren
    HealthBar::HealthBar(float unitPosX, float unitPosY)
    {
        rectangleGreen.setFillColor({0, 255, 0});
        rectangleGreen.setPosition({unitPosX, unitPosY - 20});

        rectangleRed.setFillColor({255, 0, 0});
        rectangleRed.setPosition({unitPosX, unitPosY - 20});

        rectangleRed.setOutlineThickness(2.f);
    }

    // Tegn healthbaren
    void HealthBar::Draw(sf::RenderWindow& window, float health, float maxHealth)
    {
        rectangleRed.setSize({20 * maxHealth, 5});
        rectangleGreen.setSize({20 * health, 5});

        window.draw(rectangleRed);
        window.draw(rectangleGreen);
    }
}