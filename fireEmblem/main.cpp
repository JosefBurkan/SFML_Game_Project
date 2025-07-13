#include "config.h"
#include "Camera/Camera.cpp"
using namespace std;
using namespace Players;
using namespace GridGenerators;
using namespace Maps;
using namespace Cameras;

int main()
{
    StartMap map{};                                 // Opprett et baneobjekt
    Camera camera{};
    map.GenerateGrid();
    GridGenerator& map1 = map.FetchGrid();   
    map.LoadWindow();    // Last inn vinduet
    sf::RenderWindow& window = map.window;

    sf::View view = camera.LoadView();                 // Last in synspunktet

    // Navn, Liv, sprite, tilknytningsbane
    Player you{"Player", 20, "prinsesse.png", map1};
    window.setFramerateLimit(30);
    window.setView(view);

    while (window.isOpen())
    {
        // Lukk programmet ved å trykke "X"
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.setView(view);
        window.clear(sf::Color(255, 255, 255, 255));
        map.DrawBackground(window);
        map.DrawMapObjects(window);
        map1.Draw(window);
        you.Draw(window);
        you.Movement();
        window.display();
    }
}


