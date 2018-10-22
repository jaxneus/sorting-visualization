cmake_minimum_required(VERSION 3.8)

project("sorting-visualization")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
find_package(SFML REQUIRED graphics window system)

set(SOURCES 
	src/main.cpp
	src/Application.h
	src/Application.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
