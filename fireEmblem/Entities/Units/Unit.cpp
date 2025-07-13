#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef UNIT_HPP
#define UNIT_HPP
using namespace std;

namespace Units {
    class Unit 
    {
        protected:  
            string name;
            int healthPoints;
            string spritePath;
            
            
        public: 
            // spritePath er for å kunne sette sprites til enheter når de opprettes
            Unit(string name, int healthPoints, string spritePath) : name(name), healthPoints(healthPoints), spritePath(spritePath)
            {
            }

            void spawn()
            {
                cout << "spawnet! \n";
            }
    };
}

#endif