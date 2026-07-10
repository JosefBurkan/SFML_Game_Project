#include "FireMageSprite.hpp"

namespace FireMageSprites
{
    FireMageSprite::FireMageSprite(sf::Texture texture)
        : Sprite()
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Prinsesse-50x50.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

    }
}