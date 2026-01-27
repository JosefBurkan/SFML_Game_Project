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
            bool firstUnit = true; // Er for å lage tidslinjen

            std::pair<int, int> GetCameraPositions(std::pair<int, int> cameraPos);
            std::vector<std::shared_ptr<Units::Unit>> GetAllUnits();
            std::shared_ptr<Units::Unit> GetUnitByTurn(int turn);       // hent uniten som har en index som matcher turnen
            void AddUnit(std::shared_ptr<Units::Unit> unit);
            void RemoveUnit();
            void UpdateUnits(sf::RenderWindow& window);
            void PerformEnemyActions(int gameTurn);
            void SortUnits();      // Sorterer units etter speed. Raskeste går først
            void DrawUnit(std::shared_ptr<Units::Unit> it, sf::RenderWindow& window);
            int GetSize();

            // Setter rekkefølgen til units i ekte tid
            // Altså den endrer seg hver runde, annerledes fra "turn" som er statisk
            void AssignOrder();   
    };
}