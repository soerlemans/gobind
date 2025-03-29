// Library Includes:
#include <gobind/gobind.hpp>

auto add(const int t_l, const int t_r) -> int
{
  return t_l + t_r;
}

auto main() -> int
{}

// Define  the simple module for the add function.
GOBIND_MODULE(simple, m)
{
  m.def("add", &add);
}


