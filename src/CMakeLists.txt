# List all source files recursively
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Create executable
add_executable(CMR_Optimisation_App_c++ ${SOURCES})
target_link_libraries(CMR_Optimisation_App_c++ pthread)

# Export compile commands for tooling (e.g., IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)