#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"

namespace UnitsManagers
{
    // Klasse for å håndtere fiender. Altså ødelegge dem når de dør, 
    // sortere dem i lister og mer
    class UnitsManager
    {
        private:
            std::vector<std::shared_ptr<Units::Unit>> units; // Pointer for å sørge at fiendene ikke kopieres inn
            int assignTurn = 0; // Sett 'turn' til units lik indeksen dems i unitlista

        public:
            void AddUnit(std::shared_ptr<Units::Unit> unit);
            std::vector<std::shared_ptr<Units::Unit>> AllUnits();
            void RemoveUnit();
            void UpdateUnits(sf::RenderWindow& window);
            void PerformEnemyActions();
            void SortUnits();      // Sorterer units etter speed. Raskeste går først
            int GetUnitByTurn(int turn);       // hent uniten som har en index som matcher turnen
            int GetSize();
    };
}