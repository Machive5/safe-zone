cmake_minimum_required(VERSION 3.14)
project(Safe_Zone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)
find_package(yaml-cpp REQUIRED)

include_directories(src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

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

add_custom_command(TARGET Safe_Zone POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Safe_Zone>/assets
)