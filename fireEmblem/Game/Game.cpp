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
        enemy1 = std::make_shared<Enemies::Enemy>(grid, map, attacks, 300, 300);
        enemy2 = std::make_shared<Slimes::Slime>(grid, map, attacks, 350, 150);
        slime2 = std::make_shared<Slimes::Slime>(grid, map, attacks, 400, 150);

        unitManager.AddUnit(enemy1);
        unitManager.AddUnit(enemy2);
        unitManager.AddUnit(slime2);
        unitManager.AddUnit(you);

        unitManager.SortUnits();

        // Shader
        shader.setSize({750.f, 800.f});
        shader.setFillColor(sf::Color(0, 0, 255, 20));

        for (int i = 0; i < unitManager.GetSize(); i++)
        {
            unitManager.GetUnitByTurn(i);
        }

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

            // Tegn bakgrunn + bane
            background1->Draw(window);
            map.DrawMapObjects(window);

            // logikk for spilleren
            // Lage noe som lignende if (turn == unitmanager.GetUnitByTurn(turn))
            // Altså turn == indeksen til en enhet i unitlista. Første unit skal ha turn 0, andre unit turn 1, osv

            if (you->turn == gameTurn)
            {

                you->Movement();

                if (lock == false)
                {
                    unitManager.GetUnitByTurn(gameTurn);
                    std::cout << "'s turn: \n";
                    lock = true;
                }
                if (!you->inMenu && you->state == "Neutral")
                {
                    gridHandler->Movement();
                }
                else if (!you->inMenu && you->state == "Selected")
                {
                    gridHandler->MovementWhileSelected();
                }
                else if (you->state == "Attack")
                {
                    gridHandler->Attack();
                }
                else if (you->state == "Finished")
                {
                    gameTurn++;
                }
            }

            unitManager.UpdateUnits(window);

            if (you->state != "Selected" && you->state != "Attack" && you->turn != gameTurn)
            {
                cooldown++;

                if (cooldown > 50)
                {
                    unitManager.PerformEnemyActions();
                    cooldown = 0;
                    gameTurn++;
                    unitManager.GetUnitByTurn(gameTurn);
                    std::cout << "'s turn: \n";
                }
            }

            if (gameTurn >= 3)
            {
                gameTurn = 0;
                you->state = "Neutral";
                lock = false;
            }

            attacks.Update();

            // Shader
            window.draw(shader);

            // Tegn grid
            gridHandler->Draw(window);

            window.display();
        }
    }
}
