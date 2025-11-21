#include "OverView.hpp"

namespace OverViews
{
    OverView::OverView()
    {
        rectangle.setFillColor({125, 0, 175});
        rectangle.setPosition({-300.f, 400});
        rectangle.setSize({250.f, 100});

        texture.loadFromFile("/Users/tastebutter/Desktop/mine_spill/fireEmblem/Assets/prinsesse_ansikt.png");

        princessFace.emplace(texture);

        princessFace->setScale({4.f, 4.f});

        font.openFromFile("/Users/tastebutter/Desktop/mine_spill/fireEmblem/Assets/Minecraft.TTF");        
    }

    sf::Text OverView::CreateText(std::string name, int health, int speed)
    {
        font.setSmooth(false); 

        sf::Text attributes(font);

        attributes.setString("Name\t" + name +"\nHealth\t" + std::to_string(health) + "\nSpeed\t" + std::to_string(speed));
        attributes.setCharacterSize(16);
        attributes.setFillColor(sf::Color::Red);

        return attributes;
    }

    void OverView::Draw(sf::RenderWindow& window , std::pair<float, float> cameraPositions, sf::Text text)
    {
        rectangle.setPosition({cameraPositions.first - 50, cameraPositions.second - 50});
        text.setPosition({cameraPositions.first - 45, cameraPositions.second - 50});
        princessFace->setPosition({cameraPositions.first + 80, cameraPositions.second - 90});
        window.draw(rectangle);
        window.draw(text);
        window.draw(*princessFace);

    }
}