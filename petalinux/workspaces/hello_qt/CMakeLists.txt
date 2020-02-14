#Specify the minimum version of CMake (3.5 is currently recommended by Qt)
cmake_minimum_required(VERSION 3.5)

# Specify project title
project(hello_qt)

# To automatically run MOC when building (Meta Object Compiler)
set(CMAKE_AUTOMOC ON)

# To automatically run UIC when building (User Interface Compiler)
set(CMAKE_AUTOUIC ON)

# To automatically run RCC when building (Resource Compiler)
set(CMAKE_AUTORCC ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Take care of Qt dependencies
find_package(Qt5 COMPONENTS Gui Qml Quick REQUIRED)

# add required source, header, ui and resource files
add_executable(${PROJECT_NAME} main.cpp qml.qrc)


# link required libs
target_link_libraries(${PROJECT_NAME} Qt5::Gui Qt5::Qml Qt5::Quick )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
