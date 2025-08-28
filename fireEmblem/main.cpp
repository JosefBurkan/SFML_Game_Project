#include "config.hpp"
#include "Camera/Camera.hpp"
#include "GridSystem/GridGenerator/GridGenerator.hpp"
#include "Entities/Units/Player/Player.hpp"
#include "Entities/Units/Enemies/Enemy.hpp"
#include "Entities/Units/Unit.hpp"
#include "Maps/MapLayouts/StartMap/StartMap.cpp"
#include "GridSystem/GridHandler/GridHandler.hpp"
#include "Maps/Background/Background1/Background1.hpp"
#include "Hitboxes/Attacks/AttackManager/AttackManager.hpp"
#include "UI/Player/Menu/Menu.hpp"

int main()
{
    StartMap map{};                                         // Opprett et baneobjekt
    map.GenerateGrid();
    GridGenerators::GridGenerator& grid = map.FetchGrid();  // Hent det genererte rutenettet
    GridHandlers::GridHandler movement(grid);             // Sett bevegelseslogikken til å fungere på det hentet rutenettet
    map.LoadWindow();    

    Cameras::Camera camera{movement};
    sf::RenderWindow& window = map.window;                  // sett 'vindu' til banen sitt 'vindu'
    sf::View view = camera.LoadView();                      // Last inn startkamera
    sf::View moveView;                                      // Funkjsonalitet for bevegelse av kamera  
    map.SetGridHandler(movement);                                        
    map.SpawnObjects();

    sf::RectangleShape shader;                              // Gjennomsiktig form som farger banen. Feks får det til å se ut som kveld
    shader.setSize({750.f, 800.f});
    shader.setFillColor(sf::Color(0, 0, 255, 20));

    Backgrounds1::Background1 background1{movement};
    background1.LoadTileMapFromFile();

    Menus::Menu menu;

    AttackManagers::AttackManager attacks;


    // rutefelt, rutefeltet til bevegelsen, banen
    Players::Player you{grid, map, attacks, movement};
    Enemies::Enemy enemy{grid, map, attacks};
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
        background1.Draw(window);
        map.DrawMapObjects(window);
        you.Movement();
        you.Draw(window);                   // Spiller

        if (you.inMenu == false && you.state == "Neutral") 
        {
            movement.Movement();
        }
        else if(you.state == "Attack")
        {
            movement.Attack();
        }

        enemy.Draw(window);
        enemy.IsHit();
        attacks.Update();

        window.draw(shader);
        grid.Draw(window);                  // Rutenett
        window.display();
    }
}


