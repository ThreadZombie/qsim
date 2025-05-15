cmake_minimum_required(VERSION 3.31)
project(qsim C)

set(CMAKE_C_STANDARD 11)

add_executable(qsim main.c complessi.c vettore_complesso.c init_parser.c)
target_link_libraries(qsim m)
