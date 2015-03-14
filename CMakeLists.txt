cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(CNC)
SET(${PROJECT_NAME} 1.0)

add_subdirectory(core)
add_subdirectory(controller)
add_subdirectory(client)

if(MSVC)
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET CNCCore PROPERTY FOLDER "Common")
endif(MSVC)