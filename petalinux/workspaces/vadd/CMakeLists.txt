cmake_minimum_required(VERSION 3.5)

project(vadd)

add_executable(${PROJECT_NAME} main.cpp xvadd.c xvadd_linux.c)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
