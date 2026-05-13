#include "Button.hpp"

namespace Buttons
{
    Button::Button(std::string contents, int destination, float posX, float posY)
        : font(std::string(ASSETS_DIR) + "ARCADECLASSIC.TTF"), 
          content(font, contents, 20) // Content må initialiseres her da den ikke har en default konstrktør
    {
        body.setPosition({posX, posY});
        body.setSize({100.f, 30.f});
        body.setFillColor({255, 0, 0});

        font.setSmooth(false); 
        content.setPosition({posX, posY});
    }

    void Button::Select()
    {
        body.setFillColor({180, 0, 0});
        content.setFillColor({210, 210, 210});
    }

    void Button::DeSelect()
    {
        body.setFillColor({255, 0, 0});
        content.setFillColor({255, 255, 255});
    }

    void Button::Draw(sf::RenderWindow& window)
    {
        window.draw(body);
        window.draw(content);
    }

}