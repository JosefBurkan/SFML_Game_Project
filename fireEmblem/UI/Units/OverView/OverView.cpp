#include "OverView.hpp"

namespace OverViews
{
    OverView::OverView()
    {
        background.setFillColor({125, 0, 175});
        background.setPosition({-300.f, 400});
        background.setSize({250.f, 100});

        princessFaceTexture.loadFromFile("/Users/tastebutter/Desktop/mine_spill/fireEmblem/Assets/prinsesse_ansikt.png");
        princessFace.emplace(princessFaceTexture);
        princessFace->setScale({4.f, 4.f});

        font.openFromFile("/Users/tastebutter/Desktop/mine_spill/fireEmblem/Assets/Minecraft.TTF"); 
        font.setSmooth(false); 
        
        timeline.setSize({400.f, 5.f});
        timeline.setFillColor(sf::Color(150, 0, 150));      
    }

    sf::Text OverView::CreateText(std::string name, int health, int speed)
    {
        sf::Text attributes(font);
        attributes.setString("Name\t" + name +"\nHealth\t" + std::to_string(health) + "\nSpeed\t" + std::to_string(speed));
        attributes.setCharacterSize(16);
        attributes.setFillColor(sf::Color::Red);

        return attributes;
    }

    void OverView::ManageTimeline(std::vector<std::shared_ptr<Units::Unit>> units, sf::RenderWindow& window, int cameraY)
    {
        for (auto unit : units)
        {
            sf::Sprite icon = unit->GetIcon();

            icon.setPosition({500.f + (unit->currentOrder * 50), cameraY + 25.f});
            window.draw(icon);
        }
    }

    void OverView::Draw(sf::RenderWindow& window, std::pair<float, float> cameraPositions, sf::Text text)
    {
        background.setPosition({cameraPositions.first - 370, cameraPositions.second + 5});
        text.setPosition({cameraPositions.first - 360, cameraPositions.second + 10});
        princessFace->setPosition({cameraPositions.first - 240, cameraPositions.second - 40});
        timeline.setPosition({cameraPositions.first + 80, cameraPositions.second + 50});

        window.draw(background);
        window.draw(text);
        window.draw(*princessFace);
        window.draw(timeline);
    }
}