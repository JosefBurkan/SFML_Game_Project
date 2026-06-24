#include "DamageNumbers.hpp"

namespace DamageNumbers
{
    DamageNumber::DamageNumber()
        : font(std::string(ASSETS_DIR) + "ARCADECLASSIC.TTF"),
        number(font)
    {
        number.setCharacterSize(25);
        number.setOutlineColor({0, 0, 0});
        number.setOutlineThickness(1.5f);
    }

    void DamageNumber::Draw(sf::RenderWindow& window)
    {

        if (timer >= 0)
        {
            window.draw(number);
            number.move({0.f, -0.1f});
            number.setFillColor({255, 0, 0, transparence});
            number.setOutlineColor({0, 0, 0, transparence});

            transparence -= 5;
            timer -= 5;
        }

    }

    void DamageNumber::PrepareDraw(std::string damageTaken, sf::Vector2f position)
    {
        position.y -= 50.f;
        position.x += 10.f;

        number.setPosition(position);
        number.setString(damageTaken);
        timer = 255;
        transparence = 255;
    }
}