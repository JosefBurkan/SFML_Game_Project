#include "Game.hpp"

namespace Games
{
    Game::Game()
        : map(),
          attacks(),
          unitManager()
    {
        // Init map
        map.GenerateGrid();

        GridGenerators::GridGenerator& grid = map.FetchGrid();
        gridHandler = std::make_unique<GridHandlers::GridHandler>(grid);
        camera = std::make_unique<Cameras::Camera>(*gridHandler);
        background1 = std::make_unique<Backgrounds1::Background1>(*gridHandler);

        map.LoadWindow();
        map.SetGridMovement(*gridHandler);
        map.SpawnObjects();

        // Init background
        background1->LoadTileMapFromFile();

        // Units
        you    = std::make_shared<Players::Player>(grid, map, attacks, *gridHandler);
        enemy1 = std::make_shared<Enemies::Enemy>(grid, map, attacks);
        enemy2 = std::make_shared<Slimes::Slime>(grid, map, attacks);

        unitManager.AddUnit(enemy1);
        unitManager.AddUnit(enemy2);
        unitManager.AddUnit(you);

        // Shader
        shader.setSize({750.f, 800.f});
        shader.setFillColor(sf::Color(0, 0, 255, 20));
    }

    void Game::Run()
    {
        sf::RenderWindow& window = map.window;
        sf::View view = camera->LoadView();
        sf::View moveView;

        window.setFramerateLimit(60);
        window.setView(view);

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            // Kamera
            moveView = camera->MoveView();
            window.setView(moveView);

            // Tegn bakgrunn + map
            background1->Draw(window);
            map.DrawMapObjects(window);

            // Spilllogikk
            you->Movement();

            if (!you->inMenu && you->state == "Neutral")
                gridHandler->Movement();
            else if (!you->inMenu && you->state == "Selected")
                gridHandler->MovementWhileSelected();
            else if (you->state == "Attack")
                gridHandler->Attack();

            unitManager.UpdateUnits(window);
            attacks.Update();

            // Shader
            window.draw(shader);

            // Tegn grid
            gridHandler->Draw(window);

            window.display();
        }
    }
}
