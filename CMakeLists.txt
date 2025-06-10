cmake_minimum_required(VERSION 3.14)
project(Safe_Zone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)
find_package(yaml-cpp REQUIRED)

include_directories(
	scene
	src/scenes
	src/system/include
	src/tools/include
)


set(SYSTEM
	src/system/Game.cpp
)

set(SOURCES
	src/main.cpp
	${SYSTEM}
)


# add_executable(final_project ${SOURCES})
add_executable(Safe_Zone ${SOURCES})

#link library
target_link_libraries(Safe_Zone 
	PRIVATE
	sfml-graphics 
	sfml-window 
	sfml-system 
	sfml-audio 
	yaml-cpp
)


# Link libraries if needed
# target_link_libraries(final_project PRIVATE some_library)