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
        fireMage  = std::make_shared<FireMages::FireMage>(gridHandler, attacks);
        slime1    = std::make_shared<Slimes::Slime>(gridHandler, attacks, 300, 150);
        slime2    = std::make_shared<Slimes::Slime>(gridHandler, attacks, 400, 150);
        swordsman = std::make_shared<Swordsmen::Swordsman>(gridHandler, attacks);

        unitManager.AddUnit(slime1, {6.f, 3.f});
        unitManager.AddUnit(slime2, {8.f, 3.f});
        unitManager.AddUnit(fireMage, {0.f, 2.f});
        unitManager.AddUnit(swordsman, {0.f, 3.f});

        unitManager.SortUnits();

        unitManager.LoadUnits();

        // Shader
        shader.setSize({1000.f, 800.f});
        shader.setFillColor(sf::Color(0, 0, 255, 20));

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

                int positionX = currentTurnUnit->GetPosition().x;
                int positionY = currentTurnUnit->GetPosition().y;

                // Hvis typen til uniten er en spiller, utfør spilleroppførsel
                if (currentTurnUnit->type == "Player" && cooldown <= 0) 
                {
                    if (!currentTurnUnit->inMenu)
                        currentTurnUnit->Movement();
                    else
                        currentTurnUnit->MenuActions();

                    if (!lock)
                    {
                        gridHandler.SelectTile(positionY, positionX);
                        std::cout << "Turn " << gameTurn + 1 << ": ";
                        std::cout << currentTurnUnit->name << "'s turn: \n";
                        currentTurnUnit->state = S::idle;
                        lock = true;
                    }

                    switch (currentTurnUnit->state)
                    {
                        case S::idle:
                            if (!currentTurnUnit->inMenu)
                                moveLock = false;
                                gridHandler.Movement();
                            
                            break;
                        
                        case S::selected:

                            if (!currentTurnUnit->inMenu)
                                gridHandler.MovementWhileSelected();
                            
                            break;

                        case S::moving:

                            if (!moveLock)
                                moveLock = true;
                                cooldownBetweenMoves = currentTurnUnit->movementTime;
                            
                            if (cooldownBetweenMoves >= 0)
                                unitManager.PerformPlayerSmoothMovement(*currentTurnUnit);
                                cooldownBetweenMoves--;
                            
                            break;
                        
                        case S::attack:

                            gridHandler.Attack();
                            break;

                        case S::attacking:

                            currentTurnUnit->attackTimer--;

                            if (currentTurnUnit->attackTimer <= 0)
                            {
                                gameTurn++;

                                unitManager.AssignOrder();

                                currentTurnUnit->attackTimer = currentTurnUnit->maxAttackTimer;
                                currentTurnUnit->state = S::idle;

                                lock = false;
                                moveLock = false;
                                cooldown = 20;
                            }
                            break;

                        case S::dying:
                            //Logikken skal flyttes hit
                            break;
                    }
                }

                // Hvis typen til uniten er en fiende, utfør fiendeoppførsel
                else if (currentTurnUnit->type == "Enemy" && currentTurnUnit->state != S::dying)
                {
                    gridHandler.SelectTile(positionY, positionX);

                    // Kalkuler ruta kun en gang  
                    if (cooldown <= 0)
                    {
                        if (!moveLock)
                        {
                            unitManager.SetEnemyPath(*currentTurnUnit);
                            currentTurnUnit->state = S::moving;
                            moveLock = true;
                            cooldownBetweenMoves = currentTurnUnit->movementTime;
                        }

                        // Beveg fienden mot spilleren til den stopper en rute forran
                        switch (currentTurnUnit->state)
                        {

                            case S::idle:

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

                                break;
                            
                            case S::moving:

                                if (currentTurnUnit->playerDetected && cooldownBetweenMoves >= 0)
                                {
                                    unitManager.PerformEnemyMovement(*currentTurnUnit);
                                    cooldownBetweenMoves--;
                                }

                                if (cooldownBetweenMoves <= 0)
                                {
                                    currentTurnUnit->state = S::idle;
                                }
                                break;
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