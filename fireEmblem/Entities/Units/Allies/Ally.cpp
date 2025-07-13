#include <iostream>
#include "../Unit.cpp"
using namespace std;
using namespace Units;

namespace Allies 
{
    class Ally : public Unit 
    {

        public:
            Ally(string name, int healthPoints, string spritePath) : Unit(name, healthPoints, spritePath)
            {

            }

            void spawn() 
            {
                cout << name << " has spawned! with health: " << healthPoints;
            }
    };
}

