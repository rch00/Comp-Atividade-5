cmake_minimum_required(VERSION 3.20)
project(minic)

set(CMAKE_C_STANDARD 11)

add_executable(regex.tester exemplos.c)
add_executable(regex lexer.c lexer.h arq.c arq.h lexertest.c)
