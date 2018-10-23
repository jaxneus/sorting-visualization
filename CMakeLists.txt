cmake_minimum_required(VERSION 3.8)

project("sorting-visualization")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(SFML_ROOT C:/code/Dependencies/SFML-2.5.1)
find_package(SFML REQUIRED graphics window system)

set(SOURCES 
	src/main.cpp
	src/Application.h
	src/Application.cpp
)

include_directories(${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
         "C:/code/Dependencies/SFML-2.5.1/bin"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>
		 )