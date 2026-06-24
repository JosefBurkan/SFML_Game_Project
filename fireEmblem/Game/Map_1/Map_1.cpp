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
        fireMage = std::make_shared<FireMages::FireMage>(gridHandler, attacks);
        slime1 = std::make_shared<Slimes::Slime>(gridHandler, attacks, 300, 150);
        slime2 = std::make_shared<Slimes::Slime>(gridHandler, attacks, 400, 150);
        swordsman = std::make_shared<Swordsmen::Swordsman>(gridHandler, attacks);

        unitManager.AddUnit(slime1);
        unitManager.AddUnit(slime2);
        unitManager.AddUnit(fireMage);
        unitManager.AddUnit(swordsman);

        unitManager.SortUnits();

        unitManager.LoadUnits();

        // Shader
        shader.setSize({1000.f, 800.f});
        shader.setFillColor(sf::Color(0, 0, 255, 20));

        swordsman->Place(0, 150);

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
        static int cooldown = 30;
        static int cooldownBetweenMoves = 30;
        static int gameTurn = 0;

        window.draw(background1);

        map.DrawMapObjects(window);

        std::shared_ptr<Units::Unit> currentTurnUnit = unitManager.GetUnitByTurn(gameTurn);

        if (gameTurn == currentTurnUnit->turn)
            {
                int positionX = currentTurnUnit->GetPosition().x / 50;
                int positionY = currentTurnUnit->GetPosition().y / 50;

                // Hvis typen til uniten er en spiller, utfør spilleroppførsel
                if (currentTurnUnit->type == "Player" && cooldown <= 0) 
                {
                    if (!currentTurnUnit->inMenu)
                    {
                        currentTurnUnit->Movement();
                    }
                    else
                    {
                        currentTurnUnit->MenuActions();
                    }

                    if (!lock)
                    {
                        gridHandler.SelectTile(positionY, positionX);
                        std::cout << "Turn " << gameTurn + 1 << ": ";
                        std::cout << currentTurnUnit->name << "'s turn: \n";
                        currentTurnUnit->state = "Neutral";
                        lock = true;
                    }

                    if (!currentTurnUnit->inMenu && currentTurnUnit->state == "Neutral")
                    {
                        moveLock = false;
                        gridHandler.Movement();
                    }
                    else if (!currentTurnUnit->inMenu && currentTurnUnit->state == "Selected")
                    {
                        gridHandler.MovementWhileSelected();
                    }
                    else if (currentTurnUnit->state == "Moving")
                    {
                        if (!moveLock)
                        {
                            moveLock = true;
                            cooldownBetweenMoves = currentTurnUnit->movementTime;
                        }
                        if (cooldownBetweenMoves >= 0)
                        {
                            unitManager.PerformPlayerSmoothMovement(*currentTurnUnit);
                            cooldownBetweenMoves--;
                        }
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

                            unitManager.AssignOrder();

                            currentTurnUnit->attackTimer = currentTurnUnit->maxAttackTimer;
                            currentTurnUnit->state = "Neutral";

                            lock = false;
                            moveLock = false;
                            cooldown = 20;
                        }
                    }
                }

                // Hvis typen til uniten er en fiende, utfør fiendeoppførsel
                else if (currentTurnUnit->type == "Enemy" && currentTurnUnit->state != "Dying")
                {
                    gridHandler.SelectTile(positionY, positionX);

                    // Kalkuler ruta kun en gang  
                    if (cooldown <= 0)
                    {
                        if (!moveLock)
                        {
                            unitManager.SetEnemyPath(*currentTurnUnit);
                            currentTurnUnit->state = "Moving";
                            moveLock = true;
                            cooldownBetweenMoves = currentTurnUnit->movementTime;
                            std::cout << "\nCBM: " << cooldownBetweenMoves;
                        }
                        // Beveg fienden mot spilleren til den stopper en rute forran
                        if (currentTurnUnit->state == "Moving")
                        {
                            if (currentTurnUnit->playerDetected && cooldownBetweenMoves >= 0)
                            {
                                unitManager.PerformEnemyMovement(*currentTurnUnit);
                                cooldownBetweenMoves--;
                            }

                            if (cooldownBetweenMoves <= 0)
                            {
                                currentTurnUnit->state = "Neutral";
                            }

                        }
                        else if (currentTurnUnit->state == "Neutral")
                        {
                            std::cout << "Turn " << gameTurn + 1 << ": ";
                            std::cout << currentTurnUnit->name << "'s turn: \n";

                            currentTurnUnit->attackTimer = currentTurnUnit->maxAttackTimer;
                            currentTurnUnit->playerDetected = false;
                            unitManager.PerformEnemyActions(*currentTurnUnit);
                            gameTurn++;
                            cooldown = 0;
                            currentTurnUnit->currentOrder = unitManager.GetSize();
                            unitManager.AssignOrder();
                            lock = false;
                            moveLock = false;
                        }
                    }


                }                   

                unitManager.UpdateUnits(window);
            }

            if (gameTurn >= unitManager.GetSize())
            {
                unitManager.firstUnit = true;
                gameTurn = 0;
                std::cout << "\n";
            }

            cooldown--;

            

            attacks.Update();

            window.draw(shader);

            gridHandler.Draw(window);

            // Oppdater tidslinjen
            overView.ManageTimeline(unitManager.GetAllUnits(), window, camera.GetPosition().second);

            unitManager.DrawOverview(window, gridHandler.GetSelectedUnit());


    }
}