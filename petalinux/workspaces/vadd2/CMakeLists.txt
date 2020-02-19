cmake_minimum_required(VERSION 3.5)

project(vadd2)

add_executable(${PROJECT_NAME} main.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
