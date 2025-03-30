# Todo implement:

add_library(
  simple SHARED
  simple.cpp
)

# Link the example with the gobind library
target_link_libraries(
  simple
  PRIVATE gobind::gobind
)

# Set the include directories so the example can find the library headers
target_include_directories(
  simple
  PRIVATE ${CMAKE_SOURCE_DIR}/src/cpp
)
