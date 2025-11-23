#include "Camera.hpp"

namespace Cameras {

    Camera::Camera(GridHandlers::GridHandler& gridHandler)
        : GridHandler(gridHandler)
    {
        

    }

    sf::View Camera::LoadView()
    {
        sf::Vector2f vec2(viewWidth, viewHeight);

        sf::Vector2f center(300, 400);
        view.setSize(vec2);
        // view.setCenter(center);

        sf::Vector2f centera = view.getCenter();
        center.x = std::round(center.x);
        center.y = std::round(center.y);
        view.setCenter(center);


        return view;
    }

    sf::View Camera::MoveView()
    {
        sf::Vector2f moveHorisontally(5.f, 0.0f);
        sf::Vector2f moveVertically(0.0f, 5.0f);
        sf::Vector2f standStill(0.0f, 0.0f);

        selectedTileX = GridHandler.SelectedTilePos().first;
        selectedTileY = GridHandler.SelectedTilePos().second;


        // det er plusset med 250, fordi viewsize teller bare fra midten av skjermen. 
        if (selectedTileY > viewSize.x + 250)
        {
            view.move(moveHorisontally);
        }
        if (selectedTileY < viewSize.x - 300)
        {
            view.move(-moveHorisontally);
        }
        if (selectedTileX > viewSize.y + 250)
        {
            view.move(moveVertically);
        }
        if (selectedTileX < viewSize.y - 300)
        {
            view.move(-moveVertically);
        }
        else 
        {
            view.move(standStill);
        }


        return view;

    }

    std::pair<int, int> Camera::GetPosition()
    {
        viewSize = view.getCenter();

        return {viewSize.x - 250, viewSize.y + 250};
    }

}