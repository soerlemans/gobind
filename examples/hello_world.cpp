// STL Includes:
#include <iostream>

// Library Includes:
#include <gobind/gobind.hpp>

auto hello_world() -> void
{
  std::cout << "Hello World!\n";
}

// Define  the simple module for the add function.
GOBIND_MODULE(hello_world, m)
{
  m.def("helloWorld", &hello_world);
}
