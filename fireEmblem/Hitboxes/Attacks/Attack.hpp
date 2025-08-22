#include "../../config.hpp"

namespace Attacks
{
    class Attack 
    {
        private:
            sf::RectangleShape hitbox;

        public:
            Attack();
            void CreateHitbox(float positionX, float positionY);
            void MoveHitbox(float positionX, float positionY);
            void Draw(sf::RenderWindow& window);
    };
}