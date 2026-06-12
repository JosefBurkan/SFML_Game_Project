#pragma once
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

            int allowTimeToFinish = 60;

            int moving = 20; // Imens en unit beveger seg    



        public:
            bool firstUnit = true; // Er for å lage tidslinjen

            std::pair<int, int> GetCameraPositions(std::pair<int, int> cameraPos);
            std::vector<std::shared_ptr<Units::Unit>> GetAllUnits();
            std::shared_ptr<Units::Unit> GetUnitByTurn(int turn);       // hent uniten som har en index som matcher turnen
            void AddUnit(std::shared_ptr<Units::Unit> unit);
            void RemoveUnit();
            void UpdateUnits(sf::RenderWindow& window);
            void LoadUnits();
            void SortUnits();      // Sorterer units etter speed. Raskeste går først

            void PerformEnemyActions(Units::Unit& currentTurnUnit);
            void PerformEnemyMovement(Units::Unit& currentTurnUnit);
            void PerformPlayerSmoothMovement(Units::Unit& currentTurnUnit);
            void SetEnemyPath(Units::Unit& currentTurnUnit);


            void DrawUnit(std::shared_ptr<Units::Unit> it, sf::RenderWindow& window);
            void DrawOverview(sf::RenderWindow& window, Units::Unit* unit);
            int GetSize();

            // Setter rekkefølgen til units i hver runde
            void AssignOrder();   
    };
}