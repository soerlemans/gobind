add_library(
  two SHARED
  two.cpp
)

# Link the example with the gobind library.
target_link_libraries(
  two
  PRIVATE gobind::gobind
)

# Set the include directories so the example can find the library headers.
target_include_directories(
  two
  PRIVATE ${CMAKE_SOURCE_DIR}/src/cpp
)
