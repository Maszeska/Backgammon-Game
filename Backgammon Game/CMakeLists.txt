cmake_minimum_required(VERSION 3.26)
project(Backgammon_Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

add_executable(Backgammon_Game main.cpp)

target_include_directories(Backgammon_Game PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(Backgammon_Game PRIVATE ${CURSES_LIBRARIES})
