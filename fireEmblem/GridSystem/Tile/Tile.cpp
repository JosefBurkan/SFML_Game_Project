#include "Tile.hpp"

namespace Tiles 
{
    
    Tiles::Tile::Tile(float x, float y)
    {
        rectangle.setSize({50.f, 50.f});
        rectangle.setFillColor(sf::Color(255, 255, 255, 0));
        rectangle.setOutlineColor(sf::Color(0, 0, 0, 250));
        rectangle.setOutlineThickness(0.f);
        rectangle.setPosition({x, y});
    }

    // Lys opp ruten om en enhet har blitt valgt
    void Tiles::Tile::ChangeColor(bool onSelect)
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

    void Tiles::Tile::Select()
    {
        rectangle.setFillColor(sf::Color(180, 200, 250, 130));
    }

    void Tiles::Tile::UnSelect() 
    {
        rectangle.setFillColor(sf::Color(255, 255, 255, 0));
    }

    const std::pair<float, float> Tiles::Tile::RetrieveTilePos() const
    {
        return {rectangle.getPosition().x, rectangle.getPosition().y};
    }

    void Tiles::Tile::Draw(sf::RenderWindow& window) {
        window.draw(rectangle);
    }
}