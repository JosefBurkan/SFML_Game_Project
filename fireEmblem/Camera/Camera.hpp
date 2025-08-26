#include "../config.hpp"
#include "../GridSystem/GridHandler/GridHandler.hpp"

namespace Cameras {
    class Camera 
    {
        private:
            sf::View view;
            float selectedTileX = 0;    // Kordinat til valgt rute 
            float selectedTileY = 0;
            int viewWidth = 600;        // Bredde på skjermen
            int viewHeight = 600;
            sf::Vector2f viewSize;
            GridHandlers::GridHandler& movement;

        public:

            Camera(GridHandlers::GridHandler& GridHandler);

            sf::View LoadView();

            sf::View MoveView();

    };

}