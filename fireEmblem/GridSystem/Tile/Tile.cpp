#include <iostream>
#include "../../config.h"
#pragma once

namespace Tiles 
{
    class Tile
    {
        public:
        sf::RectangleShape rectangle;
        int yes = 3;

            Tile() : Tile(0.f, 0.f) {}
            
            Tile(float x, float y)
            {
                rectangle.setSize({50.f, 50.f});
                rectangle.setFillColor(sf::Color(255, 255, 255, 0));
                rectangle.setOutlineColor(sf::Color(0, 0, 0, 250));
                rectangle.setOutlineThickness(0.f);
                rectangle.setPosition({x, y});
            }

            // Lys opp ruten om en enhet har blitt valgt
            void ChangeColor(bool onSelect)
            {
                if (onSelect == true)
                {
                    rectangle.setOutlineColor(sf::Color(115, 50, 250));
                    rectangle.setOutlineThickness(5.f);
                }
                else
                {
                    rectangle.setOutlineColor(sf::Color(0, 0, 0, 125));
                    rectangle.setFillColor(sf::Color(255, 255, 255, 0));
                    rectangle.setOutlineThickness(0.f);
                }
            }

            void Select()
            {
                rectangle.setFillColor(sf::Color(180, 200, 250, 130));
            }

            void UnSelect() 
            {
                rectangle.setFillColor(sf::Color(255, 255, 255, 0));
            }

            const std::pair<float, float> RetrieveTilePos() const
            {
                return {rectangle.getPosition().x, rectangle.getPosition().y};
            }

            void Draw(sf::RenderWindow& window) {
                window.draw(rectangle);
            }

    };

}