#include "config.hpp"
#include "Camera/Camera.hpp"
#include "GridSystem/GridGenerator/GridGenerator.hpp"
#include "Entities/Units/Player/Player.hpp"
#include "Entities/Units/Allies/Ally.cpp"
#include "Entities/Units/Unit.hpp"
#include "Maps/StartMap/StartMap.cpp"
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
    map.SetGridMovement(movement);                                        
    map.SpawnObjects();

    sf::RectangleShape shape;
    shape.setSize({750.f, 800.f});
    shape.setFillColor(sf::Color(0, 0, 255, 65));



    // Navn, Liv, sprite, rutefelt, rutefeltet til bevegelsen, banen
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
        moveView = camera.MoveView();       // Kamera
        window.setView(moveView);

        map.DrawBackground(window);         // Bane
        map.DrawMapObjects(window);

        you.Draw(window);                   // Spiller
        you.Movement();
        movement.Movement();

        window.draw(shape);

        grid.Draw(window);                  // Rutenett


        window.display();
    }
}


