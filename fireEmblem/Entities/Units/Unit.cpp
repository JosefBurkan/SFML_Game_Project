#include "Unit.hpp"

namespace Units 
{
    // spritePath er for å kunne sette sprites til enheter når de opprettes
    Unit::Unit(std::string name, int healthPoints, std::string spritePath, GridGenerators::GridGenerator& gridReference) 
            : name(name), healthPoints(healthPoints), spritePath(spritePath), gridGenerator(gridReference)
    {

    }
    
    void Unit::spawn()
    {
        std::cout << "spawnet! \n";
    }
    
    std::pair<int, int> Unit::RetriveCoordinations() 
    {

    }
}
