add_library(
  calling_convention SHARED
  calling_convention.cpp
)

# Link the example with the gobind library.
target_link_libraries(
  calling_convention
  PRIVATE gobind::gobind
)

# Set the include directories so the example can find the library headers.
target_include_directories(
  calling_convention
  PRIVATE ${CMAKE_SOURCE_DIR}/src/cpp
)
