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

            // Hent uniten med indeksen lik turnen
            // Dette fungerer fordi jeg har sortert dem etter fart
            // Gi kontroll til den unit som skal bevege seg denne runden
            auto currentTurnUnit = unitManager.GetUnitByTurn(gameTurn);

            // Dette er hva som kjører det turn-baserte systemet
            // Sammenligner runden med units sine interne turns
            // Alle units blir tilgitt en "intern turn" lik sin index i unit-lista
            if (gameTurn == currentTurnUnit->turn)
            {
                // Hvis typen til uniten er en spiller, utfør spilleroppførsel
                if (currentTurnUnit->type == "Player") 
                {
                    you->Movement();

                    if (lock == false)
                    {
                        std::cout << "Turn " << gameTurn << ": ";
                        std::cout << currentTurnUnit->name << "'s turn: \n";
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
                // Hvis typen til uniten er en fiende, utfør fiendeoppførsel
                else if (currentTurnUnit->type == "Enemy")
                {
                    cooldown++;

                    if (cooldown > 30)
                    {
                        unitManager.PerformEnemyActions(gameTurn);
                        cooldown = 0;
                        std::cout << "Turn " << gameTurn << ": ";
                        std::cout << currentTurnUnit->name << "'s turn: \n";
                        gameTurn++;
                    }
                }

                unitManager.UpdateUnits(window);
            }

            // Hvis runden er lik eller større enn antall units i spillet
            if (gameTurn >= unitManager.GetSize())
            {
                gameTurn = 0;
                you->state = "Neutral";
                lock = false;
                std::cout << "\n";
            }

            attacks.Update();

            // Shader
            window.draw(shader);

            // Tegn grid
            gridHandler->Draw(window);

            overView.Draw(window, camera->GetPosition(), overView.CreateText(you->name, you->healthPoints, you->speed));

            window.display();
        }
    }
}
