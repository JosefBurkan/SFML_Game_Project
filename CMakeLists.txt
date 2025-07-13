cmake_minimum_required(VERSION 3.15)
project(FireEmblem)

set(CMAKE_CXX_STANDARD 17)

# Tell CMake where to find your local SFML
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/Dependencies/SFML")

# You may need to set this policy to use SFML_ROOT properly
cmake_policy(SET CMP0074 NEW)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)


add_executable(fireEmblem fireEmblem/main.cpp)

target_include_directories(fireEmblem PRIVATE ${SFML_ROOT}/include)
target_link_libraries(fireEmblem
    ${SFML_ROOT}/lib/libsfml-graphics.dylib
    ${SFML_ROOT}/lib/libsfml-window.dylib
    ${SFML_ROOT}/lib/libsfml-system.dylib
)
