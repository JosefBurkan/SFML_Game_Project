#include "config.h"
#include "Camera/Camera.cpp"
using namespace std;
using namespace Players;
using namespace GridGenerators;
using namespace Maps;
using namespace Cameras;
using namespace GridMovements;

int main()
{
    StartMap map{};                                 // Opprett et baneobjekt
    map.GenerateGrid();
    GridGenerator& map1 = map.FetchGrid();  
    GridMovement movement(map1);
    map.LoadWindow();    

    Camera camera{movement};
    sf::RenderWindow& window = map.window;          // sett 'vindu' til banen sitt 'vindu'
    sf::View view = camera.LoadView();
    sf::View moveView;


    // Navn, Liv, sprite, tilknytningsbane
    Player you{"Player", 20, "prinsesse.png", map1, movement};
    window.setFramerateLimit(60);
    window.setView(view);




    while (window.isOpen())
    {
        // Lukk programmet ved å trykke "X"
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        moveView = camera.MoveView();
        window.setView(moveView);
        window.clear(sf::Color(255, 255, 255, 255));
        map.DrawBackground(window);
        map.DrawMapObjects(window);
        map1.Draw(window);
        you.Draw(window);
        you.Movement();
        movement.Movement();
        window.display();
    }
}


