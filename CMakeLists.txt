cmake_minimum_required(VERSION 3.8)

project("sorting-visualization")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(SFML_ROOT C:/code/Dependencies/SFML-2.5.1)
find_package(SFML REQUIRED graphics window system)

find_package(OpenGL REQUIRED)

set(SOURCES 
	src/main.cpp
	src/Application.h
	src/Application.cpp
	src/State.h
	src/Algorithm.h
)

set(SOURCES_IMGUI
	src/imgui/imconfig.h
	src/imgui/imgui.cpp
	src/imgui/imgui.h
	src/imgui/imgui_demo.cpp
	src/imgui/imgui_draw.cpp
	src/imgui/imgui_internal.h
	src/imgui/imgui_widgets.cpp
	src/imgui/imstb_rectpack.h
	src/imgui/imstb_textedit.h
	src/imgui/imstb_truetype.h
	src/imgui/imgui-SFML.cpp
	src/imgui/imgui-SFML.h
)

include_directories(${OPENGL_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES_IMGUI} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
         "C:/code/Dependencies/SFML-2.5.1/bin"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>
		 )