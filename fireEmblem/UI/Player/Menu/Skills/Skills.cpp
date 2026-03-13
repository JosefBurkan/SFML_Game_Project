#include "Skills.hpp"

namespace Skillss
{
    Skills::Skills(std::array<std::string, 3> menutext)
        : Menu(menutext)
    {
        optionsMenu.setSize({100, 200});
        optionsMenu.setFillColor({100, 200, 150, 180});
        optionsMenu.setOutlineColor({0, 0, 0, 255});
        optionsMenu.setOutlineThickness(3.f);

        arrow.setFillColor({255, 255, 255});
        arrow.setSize({20, 20});
    }
}