cmake_minimum_required(VERSION 2.6)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ../include)

add_executable(Tic-Tac-Toe ../src/main.cpp ../src/Button.cpp)
target_link_libraries(Tic-Tac-Toe ${SDL2_LIBRARIES})
