cmake_minimum_required(VERSION 3.24)
project(hexxagon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES main.cpp)
add_executable(main.cpp ${SOURCE_FILES})
include_directories(/usr/local/include)

add_executable(hexxagon main.cpp Board.cpp HexCell.cpp Game.cpp Game.h GUI.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(hexxagon sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
