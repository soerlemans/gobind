# Set minimum CMake version.
cmake_minimum_required(VERSION 3.22)

# Define the project.
project(
  gobind
  VERSION 0.0.0
  DESCRIPTION ""
  LANGUAGES CXX C
)

# Set the target variables.
include(cmake/targets.cmake)

# set(TARGET_CROW "crow")
# add_executable(${TARGET_CROW})

set_target_properties(
  ${TARGET_CROW}
  PROPERTIES
  EXPORT_COMPILE_COMMANDS ON
)

# Configure the compiler.
include(cmake/compiler.cmake)

# Configure clang-tidy.
include(cmake/clang-tidy.cmake)

# Add dependencies.
include(cmake/dependencies.cmake)

# Define src/ as include directory.
target_include_directories(
  ${TARGET_CROW_LIB}
  PUBLIC src/
)

# Compile sources.
add_subdirectory(src)
target_link_libraries(
  ${TARGET_CROW}
  PUBLIC ${TARGET_CROW_LIB})

# Build tests:
if(DEFINED CROW_BUILD_TESTS)
  include(cmake/dependencies/catch2.cmake)

  add_subdirectory(tests)
endif()
