cmake_minimum_required(VERSION 3.5)

project(CMR_Optimisation_App_c++ LANGUAGES CXX)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # c++23 is required for this project to build
set(CMAKE_CXX_EXTENSIONS OFF)  # This ensures -std=c++23 is used instead of -std=gnu++23

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g")

set(HEADERS_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)

# Automatically include all directories under include
include_directories(${HEADERS_DIR}/graph)
include_directories(${HEADERS_DIR}/robot)
include_directories(${HEADERS_DIR}/task)
include_directories(${HEADERS_DIR}/web)

# Add source and test subdirectories
add_subdirectory(${SOURCES_DIR})
add_subdirectory(${TESTS_DIR})