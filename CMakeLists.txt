cmake_minimum_required(VERSION 3.10)
project(SFML-Project)
include_directories(
    ${CMAKE_SOURCE_DIR}/SFML/include
)
link_directories(
    ${CMAKE_SOURCE_DIR}/SFML/lib
)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall -g")
add_executable(SFML-Project main.cpp)
target_link_libraries(SFML-Project
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
    sfml-audio
)
add_executable(main_test main_test.cpp main.cpp)
enable_testing()
add_test(NAME main_test COMMAND main_test --force-colors -d)