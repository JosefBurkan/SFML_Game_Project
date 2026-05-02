#pragma once
#include "../Attack/Attack.hpp"
#include "../Attack/RangedAttack/RangedAttack.hpp"

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
            std::vector<std::unique_ptr<Attacks::Attack>> activeAttacks;    // Vector som eksisterer for å ødelegge 'attack' etter en stund

            AttackManager();
            void CreateAttack(std::string source, int atkValue, float x, float y);
            void CreateRangedAttack(std::string source, int atkValue, float x, float y, std::pair<int, int> directions);
            void Draw(sf::RenderWindow& window);
            void Update();
            void Clear();
    };
}