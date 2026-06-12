#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"

namespace OverViews
{
    // Denne klassen handler om å lage et grensesnitt for karakterer
    // Når man holder over dem, skal det vise navnet dems, og litt mer informasjon nede i venstre hjørne
    // Og et bilde av karakteren
    class OverView
    {
        private:
            sf::RectangleShape background;

            sf::Font font;

            sf::Texture unitFaceTexture;
            std::optional<sf::Sprite> unitFace;

            sf::Texture princessIconTexture;
            std::optional<sf::Sprite> princessIcon;

            sf::Texture slimeIconTexture;
            std::optional<sf::Sprite> slimeIcon;

            sf::RectangleShape timeline;    // Vil vise rekkefølgen som units beveger seg i
            
        public:
            OverView();
            sf::Text CreateText(Units::Unit* unit);
            void ManageTimeline(std::vector<std::shared_ptr<Units::Unit>> units, sf::RenderWindow& window, int cameraY);   // Håndterer tidslinjen som viser rekkefølgen til units
            void Draw(sf::RenderWindow& window, sf::Text text, sf::Texture texture);
            
    };
}