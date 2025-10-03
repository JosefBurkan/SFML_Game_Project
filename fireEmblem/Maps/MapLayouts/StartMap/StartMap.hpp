#pragma once
#include "../Map/Map.hpp"

namespace StartMaps
{
    class StartMap : public Maps::Map
    {
        private:
            unsigned int numberOfColumns = 15;
            unsigned int numberOfRows = 16; 

        public:
            void GenerateGrid();
            void LoadWindow();
    };
}