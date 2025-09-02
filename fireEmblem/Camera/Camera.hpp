#include "../config.hpp"
#include "../GridSystem/GridHandler/GridHandler.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/GridMovement/GridMovement.hpp"

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
            GridHandlers::GridHandler& GridHandler;

        public:

            Camera(GridHandlers::GridHandler& gridHandler);

            sf::View LoadView();

            sf::View MoveView();

    };

}