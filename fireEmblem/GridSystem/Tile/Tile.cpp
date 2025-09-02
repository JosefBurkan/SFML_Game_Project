#include "Tile.hpp"

namespace Tiles 
{
    
    Tile::Tile(float x, float y)
    {
        rectangle.setSize({50.f, 50.f});
        rectangle.setFillColor(sf::Color(255, 255, 255, 0));
        rectangle.setOutlineColor(sf::Color(0, 0, 0, 0));
        rectangle.setOutlineThickness(3.f);
        rectangle.setPosition({x, y});
    }

    // Lys opp ruten om en enhet har blitt valgt
    void Tile::ChangeColor(bool onSelect)
    {
        if (onSelect == true)
        {
            rectangle.setOutlineColor(sf::Color(115, 50, 250, 255));
            rectangle.setOutlineThickness(5.f);
            a = true;
        }
        else
        {
            rectangle.setOutlineColor(sf::Color(0, 0, 0, 0));
            rectangle.setFillColor(sf::Color(255, 255, 255, 0));
            rectangle.setOutlineThickness(3.f);
            a = false;
        }
    }

    void Tile::Highlight(std::pair<float, float> playerPosition, int gridSizeX, int gridSizeY)
    {
        if (playerPosition.first > 0 && playerPosition.first < gridSizeX)
        {
            rectangle.setOutlineColor(sf::Color(255, 0, 255, 255));
            rectangle.setOutlineThickness(3.f);
        }
    }

    void Tile::MarkPath()
    {
        rectangle.setOutlineColor(sf::Color(100, 100, 255, 255));
        rectangle.setOutlineThickness(2.f);
    }

    void Tile::MarkAttackRange()
    {
        rectangle.setOutlineColor(sf::Color(255, 100, 100, 255));
        rectangle.setOutlineThickness(4.f);
    }

    void Tile::Select()
    {
        rectangle.setFillColor(sf::Color(180, 200, 250, 130));
    }

    void Tile::UnSelect() 
    {
        rectangle.setFillColor(sf::Color(255, 255, 255, 0));
    }

    const std::pair<float, float> Tile::RetrieveTilePos() const
    {
        return {rectangle.getPosition().x, rectangle.getPosition().y};
    }

    void Tile::Draw(sf::RenderWindow& window) {
        if (a == true || inRange == true)
        {
            window.draw(rectangle);
        }
    }
}