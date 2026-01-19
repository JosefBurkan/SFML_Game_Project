#pragma once
#include "../Map/Map.hpp"

namespace StartMaps
{
    class StartMap : public Maps::Map
    {
        private:
            unsigned int numberOfColumns = 20;
            unsigned int numberOfRows = 16; 

        public:
            void LoadWindow();
    };
}