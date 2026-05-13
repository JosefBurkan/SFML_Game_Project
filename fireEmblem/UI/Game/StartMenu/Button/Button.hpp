#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"

namespace Buttons
{
    // Knapp for hovedmenyen
    class Button
    {
        private:
            sf::RectangleShape body;
            sf::Font font;
            sf::Text content;

        public:
            Button(std::string contents, int destination, float posX, float posY);  // Hva knappen sier, hvor knappen skal ta brukeren
            void Select();
            void DeSelect();
            void Draw(sf::RenderWindow& window);
    };
}