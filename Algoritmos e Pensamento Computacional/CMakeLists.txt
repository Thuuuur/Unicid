cmake_minimum_required(VERSION 3.26)
project(Algoritmo C)

set(CMAKE_C_STANDARD 11)

# pasta onde os .exe vão ser salvos
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

add_executable(Ex_bottons Ex_bottons.c)
add_executable(Ex_for Ex_for.c)
add_executable(Ex_if_else Ex_if_else.c)
add_executable(Ex_perimetro Ex_perimetro.c)
add_executable(Ex_tabuada Ex_tabuada.c)
add_executable(Ex_while Ex_while.c)
add_executable(Ex_ Ex_.c)
