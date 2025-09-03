#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"

// Denne klassen skal være det som kobler flere av objekter sammen.
// En "Unit" liste som utfører .IsHit() når enheter treffes, for eksempel

namespace Games
{
    class Game
    {
        public:
            Units::Unit unit;
    }
}