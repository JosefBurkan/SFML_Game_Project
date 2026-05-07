#include "Button.hpp"

namespace Buttons
{
    Button::Button(std::string contents, int destination, float posX, float posY)
    {
        body.setPosition({posX, posY});
        body.setSize({100.f, 30.f});
        body.setFillColor({255, 0, 0});
    }

    void Button::Select()
    {
        body.setFillColor({180, 0, 0});
    }

    void Button::DeSelect()
    {
        body.setFillColor({255, 0, 0});
    }


    void Button::Draw(sf::RenderWindow& window)
    {
        window.draw(body);
    }
    


}