cmake_minimum_required(VERSION 3.5)

project(gpio_test)

add_executable(${PROJECT_NAME} main.c gpio_utils.c)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
