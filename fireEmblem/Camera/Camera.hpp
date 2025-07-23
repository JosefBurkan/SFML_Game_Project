#include "../config.hpp"
#include "../GridSystem/GridMovement/GridMovement.hpp"

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
            GridMovements::GridMovement& movement;

        public:

            Camera(GridMovements::GridMovement& gridMovement);

            sf::View LoadView();

            sf::View MoveView();

    };

}