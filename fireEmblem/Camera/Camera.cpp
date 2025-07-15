#include "../config.h"
using namespace GridMovements;


namespace Cameras {
    class Camera 
    {
        private:
            sf::View view;
            float selectedTileX = 0;    // Kordinat til valgt rute 
            float selectedTileY = 0;
            int viewWidth = 600;
            int viewHeight = 600;
            sf::Vector2f viewSize;
            GridMovement& movement;
            sf::Rect<float> currentView;

        public:

            Camera(GridMovement& gridMovement)
                : movement(gridMovement)
            {

            }

            sf::View LoadView()
            {
                sf::Vector2f vec1(0.f, 0.0f);
                sf::Vector2f vec2(viewWidth, viewHeight);

                sf::Vector2f center(300.f, 300.f);
                view.setSize(vec2);
                view.setCenter(center);

                return view;
            }

            sf::View MoveView()
            {
                sf::Vector2f moveHorisontally(5.f, 0.0f);
                sf::Vector2f moveVertically(0.0f, 5.0f);
                sf::Vector2f standStill(0.0f, 0.0f);

                selectedTileX = movement.SelectedTilePos().first;
                selectedTileY = movement.SelectedTilePos().second;

                viewSize = view.getCenter();

                if (selectedTileX > viewSize.x + 250)
                {
                    view.move(moveHorisontally);
                }
                if (selectedTileX < viewSize.x - 300)
                {
                    view.move(-moveHorisontally);
                }
                if (selectedTileY > viewSize.y + 250)
                {
                    view.move(moveVertically);
                }
                if (selectedTileY < viewSize.y - 300)
                {
                    view.move(-moveVertically);
                }

                else 
                {
                    view.move(standStill);
                }

                return view;

            }

    };

}