cmake_minimum_required(VERSION 3.15)
project(FireEmblem)

set(CMAKE_CXX_STANDARD 17)

# Tell CMake where to find your local SFML
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/Dependencies/SFML")

# You may need to set this policy to use SFML_ROOT properly
cmake_policy(SET CMP0074 NEW)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)


add_executable(fireEmblem
    fireEmblem/main.cpp
    fireEmblem/GridSystem/GridMovement/GridMovement.cpp
    fireEmblem/GridSystem/GridGenerator/GridGenerator.cpp
    fireEmblem/GridSystem/Tile/Tile.cpp
    fireEmblem/Entities/Units/Player/Player.cpp
    fireEmblem/Entities/Units/Unit.cpp
    fireEmblem/Maps/MapLayouts/Map/Map.cpp
    fireEmblem/Maps/Background/BackgroundTiles/BackgroundTile.cpp
    fireEmblem/Maps/Background/Background1/Background1.cpp
    fireEmblem/Entities/MapObjects/MapObject.cpp
    fireEmblem/Entities/MapObjects/Bat/Bat.cpp
    fireEmblem/Entities/MapObjects/Wall/Wall.cpp
    fireEmblem/Camera/Camera.cpp
    fireEmblem/UI/Player/Menu/Menu.cpp
)

target_include_directories(fireEmblem PRIVATE ${SFML_ROOT}/include)
target_link_libraries(fireEmblem
    ${SFML_ROOT}/lib/libsfml-graphics.dylib
    ${SFML_ROOT}/lib/libsfml-window.dylib
    ${SFML_ROOT}/lib/libsfml-system.dylib
)
