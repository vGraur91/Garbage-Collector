cmake_minimum_required(VERSION 3.28)
project(Garbage_Collector C)

set(CMAKE_C_STANDARD 11)

add_executable(Garbage_Collector main.c
        Collector.h
        Collector.c)
