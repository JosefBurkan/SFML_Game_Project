#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Units/Health/HealthBar.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Units/OverView/OverView.hpp"

namespace UnitsManagers
{
    // Klasse for å håndtere fiender. Altså ødelegge dem når de dør, 
    // sortere dem i lister og mer
    class UnitsManager
    {
        private:
            OverViews::OverView overView;
            std::vector<std::shared_ptr<Units::Unit>> units; // Pointer for å sørge at fiendene ikke kopieres inn
            int assignTurn = 0; // Sett 'turn' til units lik indeksen dems i unitlista   
            std::pair<int, int> cameraPositions; 

        public:
            void AddUnit(std::shared_ptr<Units::Unit> unit);
            std::vector<std::shared_ptr<Units::Unit>> GetAllUnits();
            void RemoveUnit();
            std::pair<int, int> GetCameraPositions(std::pair<int, int> cameraPos);
            void UpdateUnits(sf::RenderWindow& window);
            void PerformEnemyActions(int gameTurn);
            void SortUnits();      // Sorterer units etter speed. Raskeste går først
            std::shared_ptr<Units::Unit> GetUnitByTurn(int turn);       // hent uniten som har en index som matcher turnen
            int GetSize();
    };
}