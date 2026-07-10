#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Sprites/Sprite.hpp"

namespace FireMageSprites
{
    class FireMageSprite : public Sprites::Sprite
    {
        private:
            sf::Texture defaultTexture;
            
        public:
            FireMageSprite(sf::Texture texture);

    };
}