#include "Map_1.hpp"    

namespace Maps1 {

    Map1::Map1()
        : map(),
        grid(map.GenerateGrid()),
        gridHandler{grid},
        background1(gridHandler),
        attacks(),
        unitManager(),
        camera{gridHandler}
    {
        
        // Koble banen og rutenettet sammen
        map.SetGridMovement(gridHandler);
        map.SpawnObjects();

        // Init background
        background1.LoadTileMapFromFile();

        // Units
        fireMage = std::make_shared<FireMages::FireMage>(grid, map, attacks, gridHandler);
        enemy1 = std::make_shared<Enemies::Enemy>(grid, map, attacks, 300, 300);
        enemy2 = std::make_shared<Slimes::Slime>(grid, map, attacks, 350, 150);
        slime2 = std::make_shared<Slimes::Slime>(grid, map, attacks, 400, 150);
        swordsman = std::make_shared<Swordsmen::Swordsman>(grid, map, attacks, gridHandler);

        unitManager.AddUnit(enemy1);
        unitManager.AddUnit(enemy2);
        unitManager.AddUnit(slime2);
        unitManager.AddUnit(fireMage);
        unitManager.AddUnit(swordsman);

        unitManager.SortUnits();

        unitManager.LoadUnits();

        // Shader
        shader.setSize({1000.f, 800.f});
        shader.setFillColor(sf::Color(0, 0, 255, 20));

        swordsman->Move(0, 150);
    }

    sf::View Map1::GetView()
    {
        sf::View exportView = camera.LoadView();
        
        return exportView;

    }

    sf::View Map1::MoveView()
    {
        sf::View moveView = camera.MoveView();
        
        return moveView;

    }

    void Map1::Run(sf::RenderWindow& window)
    {

        window.draw(background1);

        map.DrawMapObjects(window);

        auto currentTurnUnit = unitManager.GetUnitByTurn(gameTurn);

        if (gameTurn == currentTurnUnit->turn)
            {
                int positionX = currentTurnUnit->RetrieveCoordinations().second / 50;
                int positionY = currentTurnUnit->RetrieveCoordinations().first / 50;

                // Hvis typen til uniten er en spiller, utfør spilleroppførsel
                if (currentTurnUnit->type == "Player") 
                {
                    currentTurnUnit->Movement();

                    if (lock == false)
                    {
                        gridHandler.SelectTile(positionY, positionX);
                        std::cout << "Turn " << gameTurn + 1 << ": ";
                        std::cout << currentTurnUnit->name << "'s turn: \n";
                        lock = true;
                    }

                    if (!currentTurnUnit->inMenu && currentTurnUnit->state == "Neutral")
                    {
                        gridHandler.Movement();
                    }
                    else if (!currentTurnUnit->inMenu && currentTurnUnit->state == "Selected")
                    {
                        gridHandler.MovementWhileSelected();
                    }
                    else if (currentTurnUnit->state == "Attack")
                    {
                        gridHandler.Attack();
                    }
                    else if (currentTurnUnit->state == "Attacking")
                    {
                        currentTurnUnit->attackTimer--;
                        
                        if (currentTurnUnit->attackTimer <= 0)
                        {
                            gameTurn++;

                            currentTurnUnit->currentOrder = unitManager.GetSize();
                            unitManager.AssignOrder();

                            currentTurnUnit->attackTimer = currentTurnUnit->maxAttackTimer;
                            currentTurnUnit->state = "Neutral";

                            lock = false;
                        }
                    }
                }

                // Hvis typen til uniten er en fiende, utfør fiendeoppførsel
                else if (currentTurnUnit->type == "Enemy" && currentTurnUnit->state != "Dying")
                {
                    cooldown++;
                    gridHandler.SelectTile(positionY, positionX);

                    if (cooldown > 30)
                    {

                        currentTurnUnit->attackTimer = currentTurnUnit->maxAttackTimer;
                        currentTurnUnit->state = "Neutral";

                        unitManager.PerformEnemyActions(gameTurn);
                        cooldown = 0;
                        std::cout << "Turn " << gameTurn + 1 << ": ";
                        std::cout << currentTurnUnit->name << "'s turn: \n";
                        gameTurn++;
                        currentTurnUnit->currentOrder = unitManager.GetSize();
                        unitManager.AssignOrder();
                        lock = false;
                    }
                }
                
                unitManager.UpdateUnits(window);
            }

            if (gameTurn >= unitManager.GetSize())
            {
                std::cout << unitManager.GetSize();
                unitManager.firstUnit = true;
                gameTurn = 0;
                std::cout << "\n";
            }

            attacks.Update();

            window.draw(shader);

            gridHandler.Draw(window);

            // Oppdater tidslinjen
            overView.ManageTimeline(unitManager.GetAllUnits(), window, camera.GetPosition().second);

            overView.Draw(window, camera.GetPosition(), overView.CreateText(fireMage->name, fireMage->currentHealth, fireMage->speed, fireMage->level));

    }
}