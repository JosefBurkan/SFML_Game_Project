#include "Game.hpp"

namespace Games
{
    Game::Game()
        : map(),
          attacks(),
          unitManager()
    {
        // Lag rutene
        map.GenerateGrid();

        GridGenerators::GridGenerator& grid = map.FetchGrid();

        // Lag en pointer til rutenettet
        gridHandler = std::make_unique<GridHandlers::GridHandler>(grid);
        camera = std::make_unique<Cameras::Camera>(*gridHandler);
        background1 = std::make_unique<Backgrounds1::Background1>(*gridHandler);

        map.LoadWindow();
        
        // Koble banen og rutenettet sammen
        map.SetGridMovement(*gridHandler);
        map.SpawnObjects();

        // Init background
        background1->LoadTileMapFromFile();

        // Units
        you    = std::make_shared<Players::Player>(grid, map, attacks, *gridHandler);
        enemy1 = std::make_shared<Enemies::Enemy>(grid, map, attacks, 300, 300);
        enemy2 = std::make_shared<Slimes::Slime>(grid, map, attacks, 350, 150);
        slime2 = std::make_shared<Slimes::Slime>(grid, map, attacks, 400, 150);
        swordsman = std::make_shared<Swordsmen::Swordsman>(grid, map, attacks, *gridHandler);

        unitManager.AddUnit(enemy1);
        unitManager.AddUnit(enemy2);
        unitManager.AddUnit(slime2);
        unitManager.AddUnit(you);
        unitManager.AddUnit(swordsman);

        unitManager.SortUnits();

        // Shader
        shader.setSize({750.f, 800.f});
        shader.setFillColor(sf::Color(0, 0, 255, 20));

        swordsman->Move(0, 150);
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

                    currentTurnUnit->Movement();

                    if (lock == false)
                    {
                        std::cout << "Turn " << gameTurn << ": ";
                        std::cout << currentTurnUnit->name << "'s turn: \n";
                        lock = true;
                    }

                    if (!currentTurnUnit->inMenu && currentTurnUnit->state == "Neutral")
                    {
                        gridHandler->Movement();
                    }
                    else if (!currentTurnUnit->inMenu && currentTurnUnit->state == "Selected")
                    {
                        gridHandler->MovementWhileSelected();
                    }
                    else if (currentTurnUnit->state == "Attack")
                    {
                        gridHandler->Attack();
                    }
                    else if (currentTurnUnit->state == "Finished")
                    {
                        gameTurn++;
                        currentTurnUnit->state = "Neutral";
                        currentTurnUnit->currentOrder = numberOfUnits;
                        unitManager.AssignOrder();
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
                        currentTurnUnit->currentOrder = numberOfUnits;
                        unitManager.AssignOrder();
                    }
                }
                
                unitManager.UpdateUnits(window);
            }

            // Hvis runden er lik eller større enn antall units i spillet
            if (gameTurn >= unitManager.GetSize())
            {
                unitManager.firstUnit = true;
                gameTurn = 0;
                lock = false;
                std::cout << "\n";
            }

            attacks.Update();

            // Shader
            window.draw(shader);

            // Tegn grid
            gridHandler->Draw(window);

            // Oppdater tidslinjen
            overView.ManageTimeline(unitManager.GetAllUnits(), window, camera->GetPosition().second);

            overView.Draw(window, camera->GetPosition(), overView.CreateText(you->name, you->healthPoints, you->speed));

            window.display();
        }
    }
}
