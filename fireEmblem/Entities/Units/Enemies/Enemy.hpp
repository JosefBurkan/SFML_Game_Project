#pragma once
#include "../../../config.hpp"
#include "../Unit.hpp"


namespace Maps {
    class Map;
}


namespace Enemies 
{
    class Enemy : public Units::Unit 
    {

        public:
            Enemy(GridGenerators::GridGenerator& gridReference, Maps::Map& map);

    };
}
