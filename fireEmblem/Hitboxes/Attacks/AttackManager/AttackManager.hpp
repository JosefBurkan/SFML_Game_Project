#pragma once
#include "../Attack/Attack.hpp"
#include "../../../config.hpp"

namespace AttackManagers
{
    // Denne klassen er ansvarlig for å håndtere angrep
    // Angrep legges til i en liste i denne klassen imens de lever
    // Unngår at hver fiende må vite om hver spiller, og motsatt
    class AttackManager
    {
        private:
            int attackLife = 0;

        public:
            std::vector<Attacks::Attack> activeAttacks;                // Vector som eksisterer for å ødelegge 'attack' etter en stund

            AttackManager();
            void CreateAttack(Attacks::Attack attack);
            void Draw(sf::RenderWindow& window);
            void Update();
    };
}