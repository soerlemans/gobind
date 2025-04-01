add_library(
  hello_world SHARED
  hello_world.cpp
)

# Link the example with the gobind library.
target_link_libraries(
  hello_world
  PRIVATE gobind::gobind
)

# Set the include directories so the example can find the library headers.
target_include_directories(
  hello_world
  PRIVATE ${CMAKE_SOURCE_DIR}/src/cpp
)
