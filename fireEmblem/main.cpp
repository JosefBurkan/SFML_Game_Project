#include "config.hpp"
#include "Camera/Camera.hpp"
#include "GridSystem/GridGenerator/GridGenerator.hpp"
#include "Entities/Units/Player/Player.hpp"
#include "Entities/Units/Enemies/Enemy.hpp"
#include "Entities/Units/Unit.hpp"
#include "Maps/MapLayouts/StartMap/StartMap.cpp"
#include "GridSystem/GridHandler/GridHandler.hpp"
#include "GridSystem/GridMovement/GridMovement.hpp"
#include "Maps/Background/Background1/Background1.hpp"
#include "Hitboxes/Attacks/AttackManager/AttackManager.hpp"
#include "UI/Player/Menu/Menu.hpp"
#include "Entities/Units/Enemies/Slime/Slime.hpp"

#include "Managers/UnitManager/UnitManager.hpp"

int main()
{
    StartMap map{};                                         // Opprett et baneobjekt
    map.GenerateGrid();
    GridGenerators::GridGenerator& grid = map.FetchGrid();  // Hent det genererte rutenettet
    GridHandlers::GridHandler gridHandler(grid);
    // GridMovements::GridMovement gridMovement(grid);
    map.LoadWindow();    

    Cameras::Camera camera{gridHandler};
    sf::RenderWindow& window = map.window;                  // sett 'vindu' til banen sitt 'vindu'
    sf::View view = camera.LoadView();                      // Last inn startkamera
    sf::View moveView;                                      // Funkjsonalitet for bevegelse av kamera  
    map.SetGridMovement(gridHandler);                                        
    map.SpawnObjects();

    sf::RectangleShape shader;                              // Gjennomsiktig form som farger banen. Feks får det til å se ut som kveld
    shader.setSize({750.f, 800.f});
    shader.setFillColor(sf::Color(0, 0, 255, 20));

    Backgrounds1::Background1 background1{gridHandler};
    background1.LoadTileMapFromFile();

    Menus::Menu menu;

    AttackManagers::AttackManager attacks;

    // rutefelt, rutefeltet til bevegelsen, banen
    auto you = std::make_shared<Players::Player>(grid, map, attacks, gridHandler);

    auto enemy1 = std::make_shared<Enemies::Enemy>(grid, map, attacks);        // Bruker bare auto her, fordi er en avansert type
    auto enemy2 = std::make_shared<Slimes::Slime>(grid, map, attacks);

    UnitsManagers::UnitsManager unitManager;
    unitManager.AddUnit(enemy1);
    unitManager.AddUnit(enemy2);
    unitManager.AddUnit(you);
    
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
        you->Movement();

        if (you->inMenu == false && you->state == "Neutral") 
        {
            gridHandler.Movement();
        }
        else if (you->inMenu == false && you->state == "Selected")
        {
            gridHandler.MovementWhileSelected();
        }
        else if(you->state == "Attack")
        {
            gridHandler.Attack();
        }
        unitManager.UpdateUnits(window);

        attacks.Update();
        window.draw(shader);
        grid.Draw(window);                  // Rutenett
        window.display();
    }
}


