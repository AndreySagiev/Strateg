cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/Program Files/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR})

add_executable(MyProject src/main.cpp)

target_link_libraries(MyProject sfml-system sfml-window sfml-graphics)

add_executable(MyProjectTests src/func_test.cpp)

target_link_libraries(MyProjectTests sfml-system sfml-window sfml-graphics)

enable_testing()
add_test(NAME MyProjectTests COMMAND MyProjectTests)
