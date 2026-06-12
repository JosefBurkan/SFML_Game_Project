#include "OverView.hpp"


namespace OverViews
{
    OverView::OverView()
    {
        background.setFillColor({125, 0, 175});
        background.setPosition({-300.f, 400});
        background.setSize({250.f, 100});

        unitFaceTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/prinsesse_ansikt.png");
        unitFace.emplace(unitFaceTexture);


        font.openFromFile(std::string(ASSETS_DIR) + "Minecraft.TTF"); 
        font.setSmooth(false); 
        
        timeline.setSize({400.f, 5.f});
        timeline.setFillColor(sf::Color(150, 0, 150));      
    }

    // Burde kanskje optimaliseres. Kjøres hver frame
    sf::Text OverView::CreateText(Units::Unit* unit)
    {
        sf::Text attributes(font);
        attributes.setString("Name\t" + unit->name +
                            "\nHealth\t" + std::to_string(unit->currentHealth) +
                            "\nSpeed\t" + std::to_string(unit->speed) +
                            "\nLevel\t" + std::to_string(unit->level));
        attributes.setCharacterSize(16);
        attributes.setFillColor(sf::Color::Red);

        return attributes;
    }

    void OverView::ManageTimeline(std::vector<std::shared_ptr<Units::Unit>> units, sf::RenderWindow& window, int cameraY)
    {
        timeline.setPosition({400, cameraY + 50.f});

        for (auto unit : units)
        {
            sf::Sprite icon = unit->GetIcon();

            icon.setPosition({500.f + (unit->currentOrder * 50), cameraY + 25.f});
            window.draw(icon);
        }

        window.draw(timeline);
    }

    void OverView::Draw(sf::RenderWindow& window, sf::Text text, sf::Texture texture)
    {
        unitFace.emplace(texture);
        unitFace->setScale({4.f, 4.f});
        unitFace->setPosition({200, 550});

        background.setPosition({50, 600});
        text.setPosition({50, 600});

        window.draw(background);
        window.draw(text);
        window.draw(*unitFace);
    }
}