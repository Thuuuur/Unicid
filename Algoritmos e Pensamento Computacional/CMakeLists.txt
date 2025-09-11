cmake_minimum_required(VERSION 3.26)
project(Algoritmo C)

set(CMAKE_C_STANDARD 11)

add_library(MinhaBiblioteca STATIC
        Ex_bottons.c
        Ex_encapsulamento.c
        Ex_for.c
        Ex_if_else.c
        Ex_NomeAoContrario.c
        Ex_perimetro.c
        Ex_tabuada.c
        Ex_while.c
        Ex_funcionario.c
        Ex_alunos.c
)