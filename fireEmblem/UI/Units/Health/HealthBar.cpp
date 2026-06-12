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
        rectangleRed.setSize({static_cast<float>(width), 5});


        rectangleRed.setOutlineThickness(2.f);
    }

    // Tegn healthbaren
    void HealthBar::Draw(sf::RenderWindow& window, int health, int maxHealth)
    {
        int greenWidth = (health % width) * 25;

        rectangleGreen.setSize({static_cast<float>(greenWidth), 5});

        window.draw(rectangleRed);
        window.draw(rectangleGreen);
    }
}