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
set(TARGET_GOBIND ${PROJECT_NAME})

# Create an alias for better usage
add_library(
  ${TARGET_GOBIND} SHARED
)

add_library(
  gobind::gobind ALIAS ${TARGET_GOBIND}
)

# Add subdirectories:
add_subdirectory(src)

# Set include directories for the library:
#target_include_directories(${TARGET_GOBIND} PUBLIC
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:include>
#)

# Specify the C++ standard
set_target_properties(
	${TARGET_GOBIND}
	PROPERTIES
	CXX_STANDARD 20
)

# Define include directories for headers
target_include_directories(
  ${TARGET_GOBIND} PUBLIC
  src/cpp/
)

# TODO: Move to cmake/install.cmake.
# Installation rules:
install(
  DIRECTORY src/cpp/gobind
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
)

install(
  DIRECTORY src/cpp/gobind
  DESTINATION include
  FILES_MATCHING PATTERN "*.hpp"
)

# Install the shared library
install(
  TARGETS gobind
  LIBRARY DESTINATION lib        # .so, .dylib
  ARCHIVE DESTINATION lib        # .a (static, optional)
  RUNTIME DESTINATION bin        # for Windows .dll, optional
)

# TODO: For fetchcontent:
# For FetchContent use, add these configuration options
# If you're using FetchContent, this can be included by other projects
#include(GNUInstallDirs)

# Optionally create an exportable config for CMake projects
#install(
#  EXPORT GoBindTarget
#  FILE GoBindConfig.cmake
#  DESTINATION lib/cmake/gobind
#)

# Build examples if specified:
if(DEFINED GOBIND_EXAMPLES)
  add_subdirectory(examples)
endif()
