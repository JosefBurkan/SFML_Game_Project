#pragma once
#include "../../../config.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Camera/Camera.hpp"

namespace OverViews
{
    // Denne klassen handler om å lage et grensesnitt for karakterer
    // Når man holder over dem, skal det vise navnet dems, og litt mer informasjon nede i venstre hjørne
    // Det kan eventuelt inneholde et bilde også
    class OverView
    {
        private:
        sf::RectangleShape rectangle;
        sf::Font font;

        sf::Texture texture;
        std::optional<sf::Sprite> princessFace;

        public:
            OverView();
            sf::Text CreateText(std::string name, int health, int speed);
            void Draw(sf::RenderWindow& window, std::pair<float, float> cameraPositions, sf::Text text);
    };
}