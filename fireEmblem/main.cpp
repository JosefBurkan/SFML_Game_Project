#include "config.hpp"
#include "Camera/Camera.hpp"
#include "GridSystem/GridGenerator/GridGenerator.hpp"
#include "Entities/Units/Player/Player.hpp"
#include "Entities/Units/Allies/Ally.cpp"
#include "Entities/Units/Unit.hpp"
#include "Maps/StartMap.cpp"
#include "GridSystem/GridMovement/GridMovement.hpp"

int main()
{
    StartMap map{};                                         // Opprett et baneobjekt
    map.GenerateGrid();
    GridGenerators::GridGenerator& grid = map.FetchGrid();  // Hent det genererte rutenettet
    GridMovements::GridMovement movement(grid);             // Sett bevegelseslogikken til å fungere på det hentet rutenettet
    map.LoadWindow();    

    Cameras::Camera camera{movement};
    sf::RenderWindow& window = map.window;                  // sett 'vindu' til banen sitt 'vindu'
    sf::View view = camera.LoadView();                      // Last inn startkamera
    sf::View moveView;                                      // Funkjsonalitet for bevegelse av kamera
    map.PositionObject();


    // Navn, Liv, sprite, tilknytningsbane
    Players::Player you{"Player", 20, "prinsesse.png", grid, movement, map};
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
        moveView = camera.MoveView();       // Relatert til kamera
        window.setView(moveView);

        map.DrawBackground(window);         // Relatert til banen
        map.DrawMapObjects(window);

        grid.Draw(window);                  // Relatert til rutenettet
  
        you.Draw(window);                   // Relatert til spilleren
        you.Movement();
        movement.Movement();

        window.display();
    }
}


