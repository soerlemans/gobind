// STL Includes:
#include <iostream>

// Library Includes:
#include <gobind/gobind.hpp>

auto hello_world() -> void
{
  std::cout << "Hello World!\n";
}

auto print(const char* t_msg = nullptr) -> void
{
  if(t_msg) {
    std::cout << t_msg << '\n';
  } else {
    std::cout << "No message\n";
  }
}

// Define  the simple module for the add function.
GOBIND_MODULE(hello_world, m)
{
  m.def("HelloWorld", &hello_world);
  m.def("Print", &print);
}
