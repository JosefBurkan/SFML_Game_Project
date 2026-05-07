#include "Game.hpp"


namespace Games
{
    Game::Game()
    {
        LoadWindow();
    }


    void Game::LoadWindow() 
    {
        newWindow.create(sf::VideoMode({1280, 720}), "AAAA ew");
    }

    void Game::Pause()
    {
        bool currentEscapeState = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);

        // Dette lager en frame som avgjører om spillet skal pauses eller ikke
        if (currentEscapeState && !previousEscapeState)
        {
            // Hopper mellom true og false
            paused = !paused;
        }

        previousEscapeState = currentEscapeState;
    }


    void Game::Run()
    {

        sf::RenderWindow& window = newWindow;

        window.setFramerateLimit(60);
        window.setView(map1.GetView());

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            Pause();

            moveView = map1.MoveView();
        
            window.setView(moveView);

            if (!paused)
            {
                // Banen, og alt som skjer på den kjører her
                map1.Run(window);
            }
            else 
            {
                menu.Run(window);

            }

            window.display();


        }
    }
}
