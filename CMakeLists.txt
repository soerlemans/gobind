# Set minimum CMake version.
cmake_minimum_required(VERSION 3.22)

# Define the project.
project(
  gobind
  VERSION 0.0.0
  DESCRIPTION ""
  LANGUAGES CXX C
)

# Enable FetchContent if required
include(FetchContent)

# Create target.
set(TARGET_GOBIND "gobind")

# Add subdirectories:
add_subdirectory(src)

# Create an alias for better usage
add_library(
  ${TARGET_GOBIND}::${TARGET_GOBIND} ALIAS ${TARGET_GOBIND}
)

# Set include directories for the library:
target_include_directories(${TARGET_GOBIND} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define include directories for headers
target_include_directories(
  ${TARGET_GOBIND} PUBLIC
  src/cpp/include
)

# Export the library for installation
install(
  TARGETS gobind
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(
  DIRECTORY src/cpp/
  DESTINATION include/
)

# For FetchContent use, add these configuration options
# If you're using FetchContent, this can be included by other projects
include(GNUInstallDirs)

# Optionally create an exportable config for CMake projects
install(
  EXPORT GoBindTarget
  FILE GoBindConfig.cmake
  DESTINATION lib/cmake/gobind
)
