cmake_minimum_required(VERSION 3.17)
project(CalculatorProject C)

set(CMAKE_C_STANDARD 11)

add_executable(CalculatorProject main.c tree.c tree.h linkedList.c linkedList.h variableList.c variableList.h stringFunctions.c stringFunctions.h)
