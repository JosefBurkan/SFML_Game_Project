#include "HealthBar.hpp"

namespace HealthBars
{
    // Opprett healthbaren
    HealthBar::HealthBar()
    {
        rectangleGreen.setFillColor({0, 255, 0});

        rectangleRed.setFillColor({255, 0, 0});
        rectangleRed.setSize({static_cast<float>(width), 5});

        rectangleRed.setOutlineThickness(2.f);
    }

    void HealthBar::SetPosition(sf::Vector2f position)
    {
        rectangleGreen.setPosition(position);
        rectangleRed.setPosition(position);
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