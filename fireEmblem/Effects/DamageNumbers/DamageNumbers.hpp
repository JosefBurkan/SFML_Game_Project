#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"

namespace DamageNumbers
{
    class DamageNumber
    {
        private:
            sf::Font font;
            sf::Text number;
            int timer = 0;
            std::uint8_t transparence = 0;
            sf::Color textColor;

        public: 
            DamageNumber();
            void Draw(sf::RenderWindow& window);
            void PrepareDraw(std::string damageTaken, sf::Vector2f position);

    };
}