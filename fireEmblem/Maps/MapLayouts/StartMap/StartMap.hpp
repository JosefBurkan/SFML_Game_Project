#pragma once
#include "../Map/Map.hpp"

namespace StartMaps
{
    class StartMap : public Maps::Map
    {
        private:
            int numberOfColumns = 10;
            int numberOfRows = 16; 

        public:
            void LoadWindow();
    };
}