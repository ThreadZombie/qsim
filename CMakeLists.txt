cmake_minimum_required(VERSION 3.31)
project(qsim C)

set(CMAKE_C_STANDARD 11)

add_executable(qsim main.c complessi.c vettore_complesso.c matrice_complessa.c init_parser.c circ_parser.c util.c)
target_link_libraries(qsim m)
