#include "../config.h"


namespace Cameras {
    class Camera 
    {

        public:
            sf::View LoadView()
            {
                sf::Vector2f vec1(0.f, 0.0f);
                sf::Vector2f vec2(400, 400);
                sf::View view(sf::FloatRect(vec1, vec2));
                return view;
            }

    };

}