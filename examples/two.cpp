// Library Includes:
#include <gobind/gobind.hpp>

auto func_one() -> const char*
{
  return "1";
}

auto func_two() -> const char*
{
  return "2";
}

// Define  the simple module for the add function.
GOBIND_MODULE(one, m)
{
  m.def("add", &func_one);
}

GOBIND_MODULE(two, m)
{
  m.def("add", &func_two);
}
